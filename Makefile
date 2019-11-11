EXTENSION = gcd        # the extensions name
DATA = gcd--0.0.1.sql  # script files to install
REGRESS = gcd_test     # our test script file (without extension)
MODULES = gcd

# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)