#include "M_bank_account.h"
#define view_balance() zircon_view_balance(b)
#define set_balance(value) zircon_set_balance(b, value)
#define deposit(value) zircon_deposit(b, value)
#define withdraw(value) zircon_withdraw(b, value)

#include "cSpec.h"

static void setup_objects_for_tests(void) {
    __init_M_bank_account();
}

void *b;
void setup_bank_object(void) {
    b = zircon_new(M_bank_account);
}

module(T_bank_account, {
    before({
        setup_objects_for_tests();
    });

    before_each(&setup_bank_object);

    describe("@M_bank_account", {
        it("is a valid object", {
            bool actual = zircon_is_a(b, "M_bank_account");
            assert_that(actual is true);
        });
    });

    describe("#set balance", {
        it("sets the total balance to the value we provide", {
            set_balance(10);
            assert_that_int(view_balance() equals to 10);
            
            set_balance(12);
            assert_that_int(view_balance() equals to 12);
            
            set_balance(42);
            assert_that_int(view_balance() equals to 42);
        });
    });

    describe("#view balance", {
        it("is initially zero", {
            assert_that_int(view_balance() equals to 0);
        });

        it("is 42 when we set the balance to 42", {
            set_balance(42);
            assert_that_int(view_balance() equals to 42);
        });
    });

    describe("#deposit", {
        it("is more than zero when adding any value", {
            deposit(21);
            assert_that(view_balance() > 0);
        });

        it("is more than balance when balance is set from before", {
            int prev = 4;
            set_balance(prev);
            deposit(38);
            assert_that(view_balance() > prev);
        });

        it("is 42 when adding 42", {
            deposit(42);
            assert_that_int(view_balance() equals to 42);
        });
    });
    
    describe("#withdraw", {
        it("is less than balance when balance is set from before", {
            int prev = 4;
            set_balance(prev);
            withdraw(2);
            assert_that(view_balance() < prev);
        });

        it("is still zero if we withdraw from empty account", {
            withdraw(2);
            assert_that_int(view_balance() equals to 0);
        });

        it("is 84 when withrawing 4 from 88", {
            set_balance(88);
            withdraw(4);
            assert_that_int(view_balance() equals to 84);
        });

        it("returns the value of the money withrawn", {
            set_balance(42);
            assert_that_int(withdraw(2) equals to 2);
        });

        it("returns zero if the account is empty", {
            assert_that_int(withdraw(42) equals to 0);
        });

        it("fails to withdraw more than the account has", {
            deposit(100);
            assert_that_int(withdraw(120) equals to 0);
        });
    });

    describe("#to string", {
        it("returns a representation of $42", {
            int cents = 4200;
            deposit(cents);

            char *actual = zircon_to_string(b);
            char *expected = "\033[38;5;78m42.00\033[0m|";
            assert_that_charptr(actual equals to expected);
        });

        it("returns a representation of $43", {
            int cents = 4300;
            deposit(cents);

            char *actual = zircon_to_string(b);
            char *expected = "\033[38;5;78m43.00\033[0m|";
            assert_that_charptr(actual equals to expected);
        });
    });
});

spec_suite({
    T_bank_account();
});

spec({
    run_spec_suite("failing");
});