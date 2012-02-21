# Standard things
sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

# Local variables
LIBDBCLIENT		:= $(d)/libdbclient.a

# Common to client and server - keep .o files in parent.
# Add db_postgresql.o, from server code dir, because the client should be able to 
# make a db connection and use PG functions.
#  Art 2/21/2012
COMMOBJ_$(d)		:= $(addprefix $(d)/../, db_common.o db_network.o db_client.o db_sort.o server/db_postgresql.o)

OBJ_$(d)		:= 

LIBDBCLIENT_OBJ		:= $(COMMOBJ_$(d)) $(OBJ_$(d))

DEP_$(d)		:= $(COMMOBJ_$(d):%=%.d) $(OBJ_$(d):%=%.d) 

CLEAN			:= $(CLEAN) \
			   $(COMMOBJ_$(d)) \
			   $(OBJ_$(d)) \
			   $(LIBDBCLIENT) \
			   $(DEP_$(d))

TGT_LIB			:= $(TGT_LIB) $(LIBDBCLIENT)

S_$(d)			:= $(notdir $(LIBDBCLIENT))

# Local rules
$(COMMOBJ_$(d)):	$(SRCDIR)/$(d)/Rules.mk
$(COMMOBJ_$(d)):	CF_TGT := -D$(DBMS) $(PGH)
$(OBJ_$(d)):		$(SRCDIR)/$(d)/Rules.mk
$(OBJ_$(d)):		CF_TGT := -D$(DBMS) $(PGH)

$(LIBDBCLIENT):		$(LIBDBCLIENT_OBJ)
			$(ARCHIVE)
			$(SLLIB)

# Shortcuts
.PHONY:	$(S_$(d))
$(S_$(d)):	%:	$(d)/%

# Standard things
-include	$(DEP_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
