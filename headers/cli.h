#if !defined(CLI_H)
#define CLI_H

extern gchar* const DB_DIR;

extern gboolean show_help;
extern gboolean read_bd;
extern gchar *bd;
extern gchar *key;
extern GOptionEntry entries[];

int initialize_cli(int argc, char **argv);

#endif // CLI_H