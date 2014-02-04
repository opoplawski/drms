-- base/drms/scripts/NetDRMS.sql
-- This script creates various database objects that partially compose DRMS

-- admin tables
create schema admin;
grant usage on schema "admin" to public;

create table admin.ns (
 name     text not null,
 nsgroup  text not null,
 owner    text not null
);

create table admin.sessionns (
 username   text not null,
 sessionns  text not null
);

grant select on "admin".sessionns to public;
grant select on "admin".ns to public;

-- Create the drms schema. It has both required and optional tables.
CREATE SCHEMA drms;
GRANT USAGE ON SCHEMA drms TO public;

-- This user is hard-coded in the DRMS C source, so it must exist. 
-- The PostgreSQL administrator account (e.g., "production") is actually an alias for this user, which 
-- has elevated privileges.
CREATE USER SUMSADMIN;
