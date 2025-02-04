#include <stdlib.h>
#include <stdbool.h>

#include <ert/util/test_util.hpp>
#include <ert/util/util.h>
#include <ert/util/int_vector.hpp>

#include <ert/ecl/nnc_index_list.hpp>

void test_create() {
    nnc_index_list_type *index_list = nnc_index_list_alloc();
    test_assert_true(nnc_index_list_is_instance(index_list));
    {
        const int_vector_type *list = nnc_index_list_get_list(index_list);
        test_assert_int_equal(0, int_vector_size(list));
    }
    nnc_index_list_free(index_list);
}

void test_content() {
    nnc_index_list_type *index_list = nnc_index_list_alloc();

    nnc_index_list_add_index(index_list, 0);
    nnc_index_list_add_index(index_list, 1);
    nnc_index_list_add_index(index_list, 2);
    nnc_index_list_add_index(index_list, 3);

    {
        const int_vector_type *list = nnc_index_list_get_list(index_list);
        test_assert_int_equal(4, int_vector_size(list));

        test_assert_int_equal(0, int_vector_iget(list, 0));
        test_assert_int_equal(1, int_vector_iget(list, 1));
        test_assert_int_equal(2, int_vector_iget(list, 2));
        test_assert_int_equal(3, int_vector_iget(list, 3));
    }
    nnc_index_list_free(index_list);
}

void test_sort_unique() {
    nnc_index_list_type *index_list = nnc_index_list_alloc();

    nnc_index_list_add_index(index_list, 3);
    nnc_index_list_add_index(index_list, 1);
    nnc_index_list_add_index(index_list, 2);
    nnc_index_list_add_index(index_list, 0);

    {
        const int_vector_type *list = nnc_index_list_get_list(index_list);
        test_assert_int_equal(4, int_vector_size(list));

        test_assert_int_equal(0, int_vector_iget(list, 0));
        test_assert_int_equal(1, int_vector_iget(list, 1));
        test_assert_int_equal(2, int_vector_iget(list, 2));
        test_assert_int_equal(3, int_vector_iget(list, 3));
    }
    nnc_index_list_add_index(index_list, 3);
    nnc_index_list_add_index(index_list, 1);
    nnc_index_list_add_index(index_list, 2);
    nnc_index_list_add_index(index_list, 0);
    {
        const int_vector_type *list = nnc_index_list_get_list(index_list);
        test_assert_int_equal(4, int_vector_size(list));

        test_assert_int_equal(0, int_vector_iget(list, 0));
        test_assert_int_equal(1, int_vector_iget(list, 1));
        test_assert_int_equal(2, int_vector_iget(list, 2));
        test_assert_int_equal(3, int_vector_iget(list, 3));
    }
    nnc_index_list_free(index_list);
}

int main(int argc, char **argv) {
    test_create();
    test_content();
    test_sort_unique();
    exit(0);
}
