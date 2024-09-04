#include <gvdb-builder.h>
#include <gvdb-reader.h>
#include <string.h>
#include <glib.h>
#include <stdio.h>
#include <cli.h>
#include <std_out.h>


GVariant* get(gchar* db_path, gchar* key){
    GvdbTable *db_table;
    GError *local_error = NULL;
    GVariant *value;

    db_table = gvdb_table_new (db_path, TRUE, &local_error);

    if (local_error){
        if (g_error_matches(local_error, g_file_error_quark(), G_FILE_ERROR_ACCES)){
            g_print("Permission denied: %s\n", db_path);
        }
        else if (g_error_matches(local_error, g_file_error_quark(), G_FILE_ERROR_NOENT)){
            g_print("No such file: %s\n", db_path);
        }
        exit(EXIT_FAILURE);
    }

    value = gvdb_table_get_value (db_table, key);

    if (!value){
        g_printerr("Key %s not found\n", key);
        exit(EXIT_FAILURE);
    }

    gvdb_table_free(db_table);

    return value;
}


GPtrArray* get_all(gchar* db_path){
    GvdbTable *db_table;
    GVariant *value;
    GString *value_str;
    GError *local_error = NULL;
    GPtrArray *entries = g_ptr_array_new();
    gchar **names;
    gsize length;

    db_table = gvdb_table_new (db_path, TRUE, &local_error);

    if ((names = gvdb_table_get_names(db_table, &length)) == NULL){
        return NULL;
    }

    for (int i = 0; i < length; i++){
        if (gvdb_table_has_value(db_table, names[i]) == TRUE){
            value = gvdb_table_get_value(db_table, names[i]);
            value_str = g_variant_print_string(value, NULL, TRUE);

            gchar **entry = g_new0(gchar *, 3);
            entry[0] = g_strdup(names[i]);
            entry[1] = g_strdup(value_str->str);
            entry[2] = NULL;
            g_ptr_array_add(entries, entry);

            g_string_free(value_str, TRUE);
            g_variant_unref(value);
        }
    }

    gvdb_table_free(db_table);

    return entries;
}


int main (int argc, char **argv)
{
    GPtrArray* all_key_value = NULL;
    GVariant* value = NULL;

    int initialize_ec = initialize_cli(argc, argv);

    if (read_bd){
        if (bd && key){
            value = get(bd, key);

            g_print("%s\n", value_to_str(value));
            g_variant_unref(value);
        }
        else if (bd){
            gchar* all_key_value_str = NULL;

            all_key_value = get_all(bd);
            all_key_value_str = all_entries_to_str(all_key_value);

            g_print("%s\n", all_key_value_str);
            g_free(all_key_value_str);
        }
        else{
            g_printerr("Key %s is specified, but no database is specified\n", key);
        }
    }

    if (all_key_value) {
        for (guint i = 0; i < all_key_value->len; i++) {
            gchar **cur = g_ptr_array_index(all_key_value, i);
            g_free(cur);
        }
        g_ptr_array_free(all_key_value, TRUE);
    }
    

    return 0;
}