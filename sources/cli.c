#include <glib.h>

gchar* const DB_DIR = "/etc/dconf/db/";

gboolean show_help = FALSE;
gboolean read_bd = FALSE;
gchar *bd = NULL;
gchar *key = NULL;

GOptionEntry entries[] = {
    {"help", 'h', 0, G_OPTION_ARG_NONE, &show_help, "Show help", NULL},
    {"read", 'r', 0, G_OPTION_ARG_NONE, &read_bd, "Database read option", NULL},
    {"database", 'd', 0, G_OPTION_ARG_STRING, &bd, "Database name in the format 'policy<UID>'", NULL},
    {"key", 'k', 0, G_OPTION_ARG_STRING, &key, "The key by which you want to get the value from the database", NULL},
    {NULL}
};

int initialize_cli(int argc, char **argv) {
    GOptionContext *context = g_option_context_new("- GVDB database utility");
    g_option_context_add_main_entries(context, entries, NULL);

    GError *error = NULL;
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_printerr("Option parsing failed: %s\n", error->message);
		exit(EXIT_FAILURE);
	}

    bd = g_strconcat(DB_DIR, bd, NULL);

    g_option_context_free(context);
	context = NULL;

    return 0;
}