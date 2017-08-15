-- TABLE HISTORY CREATION
--- Creates history tables for all tables in schema public 
---- Consists of copy of all columns and aditional
----- Type of operation being done to a tuple, date_time of execution, userid (who did it)

DO $$declare 
		public_tables_c cursor for select table_name from information_schema.tables where table_schema = 'public' and table_name !~ 'history_';
		public_table record;
		
begin
		open public_tables_c;
		LOOP

			fetch public_tables_c into public_table;
			exit when not found;
			
			execute 'CREATE TABLE IF NOT EXISTS history_'|| public_table.table_name ||' as select * from '|| public_table.table_name ||';';
			
			execute 'alter table history_'|| public_table.table_name ||' 
						add column if not exists operation_type text not null, 
						add column if not exists date_time timestamp not null, 
						add column if not exists userid text not null, 
						add column if not exists TABLE_NAME text not null;';
									
		end LOOP;
		close public_tables_c;
--	return 1;
end$$;

-- 'table_name ~ history' <- if it matches

-- functions executed by triggers
--- Creates triggers for all tables named history_<name>
---- on operations INSERT, DELETE and UPDATE
DO $$declare 
		public_tables_c cursor for select table_name from information_schema.tables where table_schema = 'public' and table_name !~ 'history_';
		public_table record;
begin
		open public_tables_c;
		LOOP

			fetch public_tables_c into public_table;

			exit when not found;
			
			-- This will create a generic historical table in which the tuple field will have all
			-- The values of the row of the original table 
			execute 'create or replace function history_trigger_'|| public_table.table_name ||'() returns trigger as $history_'||public_table.table_name||'$
					begin
						if (TG_OP =''INSERT'') then
							insert into history_' || public_table.table_name || ' select  NEW.*,''INSERT'', now() , user, TG_TABLE_NAME::TEXT;
							return NEW;
						elseif (TG_OP = ''DELETE'') then
							insert into history_' || public_table.table_name || ' select  OLD.*,''DELETE'', now(), user,  TG_TABLE_NAME::TEXT;
							return OLD;
						elseif (TG_OP = ''UPDATE'') then
							insert into history_' || public_table.table_name || ' select NEW.*, ''UPDATE'',now(), user,  TG_TABLE_NAME::TEXT;
							return NEW;
						end if;
							return null;
					end;

					$history_'||public_table.table_name||'$ language plpgsql;';


			
		end LOOP;
		close public_tables_c;
--	return 1;
end$$;

-- TRIGGERS FOR INSERT, DELETE and UPDATE
--- creates triggers for every table named history_<name> in public schema

DO $$declare 
		public_tables cursor for select table_name from information_schema.tables where table_schema = 'public' and table_name !~ 'history_';
		public_table record;
		table record;
begin
		open public_tables;
		LOOP
			fetch public_tables into public_table;

			exit when not found;
			
			execute 'drop trigger if exists trigger_history_'
			|| public_table.table_name ||' on '||public_table.table_name||'';
			execute 'create trigger trigger_history_'
			|| public_table.table_name ||' after insert or update or delete on '
			|| public_table.table_name ||' for each row execute procedure history_trigger_'|| public_table.table_name ||'();';

		end LOOP;
		close public_tables;
end$$;

