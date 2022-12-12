#include <gtk/gtk.h>


void
on_t1_toggled                          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_t2_toggled                          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_t3_toggled                          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_aff_clicked                         (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ajout_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treels_row_activated                (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_re_clicked                          (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_listadd_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_vote1_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_main_liste_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treecond_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_modif_liste_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ajout_cond_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_vote2_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_Return_liste_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_listes_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_stat_clicked                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_suprimer_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
