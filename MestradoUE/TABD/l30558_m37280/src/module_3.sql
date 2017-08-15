
DO $$declare 
		-- CURSORS
		public_tables_c cursor for select table_name from information_schema.tables where table_schema = 'public' and table_name !~ 'history_';
		public_tables_column_c refcursor;
		public_table_pkey refcursor;

		-- RECORDS
		public_table record;
		public_column record;
		table_pkey record;

		atributes text;
		atributes_data text;

		pkey text;
		pkey_data text;
		pkey_check_flag integer;
		table_name_text text;
		format_args text;

begin
		
		open public_tables_c;
		LOOP
			pkey_check_flag = 1;
			fetch public_tables_c into public_table;

			
			exit when not found;
			
			atributes = 'userid';
			atributes_data = 'userid text';
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
														and table_schema = 'public' 
														and table_name = 'history_'||public_table.table_name;
			
			fetch public_table_pkey into table_pkey; 
			LOOP 

				fetch public_tables_column_c into public_column;
				exit when not found;

				atributes = atributes || ', ' || public_column.column_name;
				atributes_data = atributes_data || ', ' || public_column.column_name || ' '|| public_column.data_type;
				
				-- ARRANGE STRINGS IN A READABLE FORMAT
				if pkey_check_flag = 1 and table_pkey.attname is not null or table_pkey.data_type is not null then 

					pkey = table_pkey.attname ||'_n '|| table_pkey.data_type;
					pkey_data =  table_pkey.attname || '= %L';	
					format_args = table_pkey.attname || '_n';		
					fetch public_table_pkey into table_pkey;
				
				end if;

				 if pkey_check_flag != 1 and table_pkey.attname is not null or table_pkey.data_type is not null then

					pkey = pkey ||', '|| table_pkey.attname ||'_n '|| table_pkey.data_type ;
					pkey_data = pkey_data || 'and ' || table_pkey.attname || '=%L';
					format_args = format_args || ', ' || table_pkey.attname || '_n';		
					fetch public_table_pkey into table_pkey;

				end if;
				-- END STRING FORMATION 

				
			-- This will create a generic historical table in which the tuple field will have all
			-- The values of the row of the original table 
			end LOOP;

			close public_tables_column_c;

			execute 'create or replace function tuple_history_'|| public_table.table_name ||'('|| pkey ||') 
						returns table('||atributes_data||') as $func$ 
							begin
								return query 
									execute format(''select '|| atributes ||' 
										from history_'|| public_table.table_name ||' 
											where '|| pkey_data ||''','||format_args||');
							end
					$func$	language plpgsql;';

			execute 'create index if not exists tuple_history_'|| public_table.table_name ||'_index  on history_'|| public_table.table_name ||'('|| atributes ||');';
			
			pkey_check_flag = 2;
			close public_table_pkey;
		
		end LOOP;
		close public_tables_c;
end$$;
