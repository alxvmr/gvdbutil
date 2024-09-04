#include <glib.h>

gchar* value_to_str(GVariant *value){
    return g_variant_print(value, TRUE);
}


gchar* all_entries_to_str(GPtrArray* entries){
    guint offset = 4;
    gchar* entries_str = "[\n";

    for (guint i = 0; i < entries->len; i++) {
        gchar** cur = g_ptr_array_index(entries, i);

        if (i > 0) {
            entries_str = g_strconcat(entries_str, ",\n", NULL);
        }

        gchar *key = cur[0];
        gchar *value = cur[1];
        entries_str = g_strconcat(entries_str, g_strdup_printf("%*s", offset, ""), "[", key, ", ", value, "]", NULL);

        g_free(key);
        g_free(value);
    }

    entries_str =  g_strdup_printf("%s\n]", entries_str);

    return entries_str;
}