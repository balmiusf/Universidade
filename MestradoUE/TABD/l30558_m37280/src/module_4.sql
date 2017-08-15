-- EVERY TABLE WILL HAVE A FUNCTION THAT RECEIVED THE PRIMARY KEYS AND TIMESTAMP AND RETURNS THE TUPLE LAST MODIFIED

DO $$declare 
		-- CURSORS
		public_tables_c cursor for select table_name from information_schema.tables where table_schema = 'public' and table_name !~ 'history_';
		public_tables_column_c refcursor;
		public_table_pkey refcursor;

		-- RECORDS
		public_table record;
		public_column record;
		table_pkey record;

		atributes text;					-- TABLE ATRIBUTES
		atributes_data text;			-- TABLE ATRIBUTES + DATA_TYPE
		pkey text;						-- PKEY
		pkey_data text;					-- PKEY + DATA_TYPE
		table_name_text text;			-- TABLE NAME 
		format_args text;				-- ARGS FOR FORMAT FUNCTION

		pkey_check_flag integer;		-- FLAG FOR PKEY STRING
		cycle_loop integer;				-- COUNT THE NUMBER OF LOOPS
begin
		
		open public_tables_c;			-- OPEN CURSOR
		LOOP 							-- STARTING FIRST LOOP
			cycle_loop = 1;				-- INITIALIZE FLAGS
			pkey_check_flag = 1;
			fetch public_tables_c into public_table;	-- FETCH

			
			exit when not found;						-- STOP WHEN THERE ARE NO MORE RESULTS
			
			atributes = '';
			atributes_data = '';
			table_name_text = ''||public_table.table_name||'';

			-- SOURCE: https://wiki.postgresql.org/wiki/Retrieve_primary_key_columns
			-- ALLOWS THE RETRIEVAL OF PRIMARY KEYS OF ANY TABLE
			open public_table_pkey for SELECT a.attname, format_type(a.atttypid, a.atttypmod) AS data_type
											FROM   pg_index i
											JOIN   pg_attribute a ON a.attrelid = i.indrelid
											                     AND a.attnum = ANY(i.indkey)
											WHERE  i.indrelid = table_name_text::regclass
											AND    i.indisprimary;

			
			-- RETRIEVE COLUMNS AND DATA_TYPE FOR THE TABLE IN QUESTION
			open public_tables_column_c for select column_name, data_type 
												from information_schema.columns 
													where column_name != 'userid' 
														and column_name != 'table_name'
														and column_name != 'operation_type'
														and column_name != 'date_time'
														and table_schema = 'public' 
														and table_name = 'history_'||public_table.table_name;
			
			fetch public_table_pkey into table_pkey;

			-- SECOND LOOP
			LOOP 

				fetch public_tables_column_c into public_column;
				exit when not found;

				-- ARRANGE STRINGS IN A READABLE FORMAT
				if cycle_loop = 1 then
					atributes = public_column.column_name;
					atributes_data = public_column.column_name || ' '|| public_column.data_type;
			
				end if;

				if cycle_loop != 1 then
					atributes = atributes || ', ' || public_column.column_name;
					atributes_data = atributes_data || ', ' || public_column.column_name || ' '|| public_column.data_type;
				end if;
				

				if pkey_check_flag = 1 and table_pkey.attname is not null or table_pkey.data_type is not null then 

					pkey = table_pkey.attname ||'_n '|| table_pkey.data_type;
					pkey_data =  table_pkey.attname || '= %L';	
					format_args = table_pkey.attname || '_n';		
					fetch public_table_pkey into table_pkey;
				
				end if;

				 if pkey_check_flag != 1 and table_pkey.attname is not null or table_pkey.data_type is not null then

					pkey = pkey ||', '|| table_pkey.attname ||'_n '|| table_pkey.data_type ;
					pkey_data = pkey_data || 'and ' || table_pkey.attname || '= %L';
					format_args = format_args || ', ' || table_pkey.attname || '_n';		
					fetch public_table_pkey into table_pkey;

				end if;
				-- END STRING FORMATION 

				cycle_loop = cycle_loop + 1;

			-- This will create a generic historical table in which the tuple field will have all
			-- The values of the row of the original table 
			end LOOP;

			close public_tables_column_c;

			-- FUNCTION THAT GIVEN PRIMARY KEYS AND TIMESTAMP RETURNS A TABLE WITH THE TUPLE VALUE THAT WAS LAST MODIFIED
			execute 'create or replace function given_tuple_time_at_'|| public_table.table_name ||'('|| pkey ||',ts text) 
						returns table('||atributes_data||') as $func$ 
							begin
								return query 
									execute format(''select '|| atributes ||' 
										from history_'|| public_table.table_name ||' 
											where  '|| pkey_data ||'  and date_time <= ''''%s'''' order by date_time desc limit 1'','||format_args||',ts);
							end
					$func$	language plpgsql;';

			-- INDEX CREATION FOR EVERY HISTORY_<name> TABLE
			execute 'create index if not exists given_tuple_time_at_history_'|| public_table.table_name ||'_index  on history_'|| public_table.table_name ||'('|| atributes ||');';
			
			pkey_check_flag = 2;
			close public_table_pkey;
		
		end LOOP;
		close public_tables_c;
end$$;

