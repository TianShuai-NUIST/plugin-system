#include "test.h"
#include "types.h"
#include <string.h>

static void test_append_increases_len_by_one(void){
  PluginList list = PLUGIN_LIST_INIT;
  Plugin p = PLUGIN_INIT;
  strncpy(p.filename, "test.plugin", sizeof(p.filename) - 1);
  p.filename[sizeof(p.filename) - 1] = '\0';
  plugin_list_append(&list, &p);
  ASSERT_EQ_INT(list.len, 1);
  plugin_list_append(&list, &p);
  ASSERT_EQ_INT(list.len, 2);
  plugin_list_free(&list);
  ASSERT_TRUE(list.plugins == NULL);
}

int main(void){
  test_append_increases_len_by_one();

  TEST_SUMMARY();
}
