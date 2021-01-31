#include "T_engine.spec.c"
#include "T_bank_account.spec.c"
#include "T_read_handler.spec.c"
#include "T_write_handler.spec.c"

#include "cSpec.h"

spec_suite({
    T_engine();
    T_bank_account();
    T_read_handler();
    T_write_handler();
});

spec({
    run_spec_suite("failing");
});
