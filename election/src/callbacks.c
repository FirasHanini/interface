#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "liste.h"
#include "utilisateur.h"
#include "condidat.h"
#include <stdio.h>
#include <string.h>
// declaration des variables 
// idl id liste pour treeview
//ida id liste pour ajout de condidat
// i_c variable togled button nombre de condidat liste
// variable test pour inetrface ajout-liste (0 ajouter une liste ; 1 modifier une liste)
int i_c=0, idl=0, ida=0, test=0;





// nombre de condidat a ajouter (window1)
void
on_t3_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){i_c=3;}
}


void
on_t2_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){i_c=2;}
}


void
on_t1_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){i_c=1;}
}








//Afficher les liste  (window2)
void
on_aff_clicked                         (GtkWidget       *objet,
                                        gpointer         user_data)
{
// Declaration
 GtkWidget *window1;
 GtkWidget *window2;
 GtkTreeView *tree;

window1=lookup_widget(objet,"window1");
window2=lookup_widget(objet,"window2");


window2=create_window2();
gtk_widget_show(window2);
gtk_widget_hide(window1);

tree=lookup_widget(window2,"treels");
afficher_liste(tree);



 
}





//ajouter une liste (window1)
void
on_ajout_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *nom;
 GtkWidget *w1;
 GtkWidget *w2;
 GtkWidget *w3;
 GtkWidget *id;
 GtkWidget *jour;
 GtkWidget *mois;
 GtkWidget *annee;
 GtkWidget *window4;
 GtkWidget *label;
 int i=0,j=0,k=0;
 char id_liste[10];
 
liste l;
//liason des fenetre
 w1=lookup_widget(objet,"window1");
 w2=lookup_widget(objet,"window2");
 w3=lookup_widget(objet,"window3");
 window4=lookup_widget(objet,"window4");
// liason des entrees
nom=lookup_widget(w1,"nom_liste");
id=lookup_widget(w1,"id_teteliste"); 
jour=lookup_widget(w1,"jour");
mois=lookup_widget(w1,"mois");
annee=lookup_widget(w1,"annee");

// les entrees
strcpy(l.nom_liste,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(l.id_tete_liste,gtk_entry_get_text(GTK_ENTRY(id)));
i=nbr_cnd( i_c);
l.nombre_condidat=i;
l.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
l.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
l.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
l.nbr_vote=0;



// test si ajout liste ou modif liste
if (test==0){
l.id_liste = id_generate();
ida=l.id_liste;
sprintf(id_liste,"%d",ida);
ajouter_liste(l);
while(j<i){
window4=create_window4();
gtk_widget_show(window4);
label=lookup_widget(window4,"lid_liste");
 gtk_label_set_text(GTK_LABEL(label),id_liste);
j++;}

}
else if (test==1){
l.id_liste=ida;
// fonction modifier 
k=modif_liste(l.id_liste,l);
test=0;
}

}






//treeview des liste (window2)
void
on_treels_row_activated                (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *Nom;
gchar *Id;
gchar *Nb_cond;

liste l;

GtkTreeModel *model =gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)){
gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &Nom, 1, &Id, 2, &Nb_cond, -1);

}


afficher_liste(treeview);
}


// recherche liste affichage (window3)
void
on_re_clicked                          (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkTreeView *tree;
 GtkWidget *rech;
 GtkWidget *window2;
 GtkWidget *window3;
 GtkWidget *nom;
 GtkWidget *id;
 GtkWidget *date;
 char tmp[30],jour[5],mois[5],annee[10];
  int idliste;

 liste k;

window3=lookup_widget(objet,"window3");
window2=lookup_widget(objet,"window2");
rech=lookup_widget(window2,"rech");

strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(rech)));


k=recherche_liste(tmp);

if (k.id_liste!=-1){
// creation d'une nouvelle fenetre
window3=create_window3();
gtk_widget_show(window3);
nom=lookup_widget(window3,"noi");
id=lookup_widget(window3,"id_t");
date=lookup_widget(window3,"date");
tree=lookup_widget(window3,"treecond");
// outputs
idl=k.id_liste;
gtk_label_set_text(GTK_LABEL(nom),k.nom_liste);
gtk_label_set_text(GTK_LABEL(id),k.id_tete_liste);
sprintf(jour,"%d",k.date.jour);
sprintf(mois,"%d",k.date.mois);
sprintf(annee,"%d",k.date.annee);
strcat(jour,"/");
strcat(jour,mois);
strcat(jour,"/");
strcat(jour,annee);
gtk_label_set_text(GTK_LABEL(date),jour);
afficher_condidat(tree, idl);

} 
else
{ idliste=atoi(tmp); 
k=recherche_liste_id(idliste);
if (k.id_liste!=-1){
// creation d'une nouvelle fenetre
window3=create_window3();
gtk_widget_show(window3);
nom=lookup_widget(window3,"noi");
id=lookup_widget(window3,"id_t");
date=lookup_widget(window3,"date");
tree=lookup_widget(window3,"treecond");
// outputs
idl=k.id_liste;
gtk_label_set_text(GTK_LABEL(nom),k.nom_liste);
gtk_label_set_text(GTK_LABEL(id),k.id_tete_liste);
sprintf(jour,"%d",k.date.jour);
sprintf(mois,"%d",k.date.mois);
sprintf(annee,"%d",k.date.annee);
strcat(jour,"/");
strcat(jour,mois);
strcat(jour,"/");
strcat(jour,annee);
gtk_label_set_text(GTK_LABEL(date),jour);
afficher_condidat(tree, idl);
}
}




}








// Ouvre window1 ajouter une liste
void
on_listadd_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window1;
 GtkWidget *window2;
 window2=lookup_widget(objet,"window2");
 window1=lookup_widget(objet,"window1");
 window1=create_window1();
 gtk_widget_show(window1);
 gtk_widget_hide(window2);

}








// ouvre (window5) fenetre de vote
void
on_vote1_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window4;
 GtkWidget *window5;
 GtkWidget *comb;
 FILE *f;
 liste l;
 f=fopen("les_liste.txt","r");
window4=lookup_widget(objet,"window4");
window5=lookup_widget(objet,"window5");
window5=create_window5();
gtk_widget_show(window5);
comb=lookup_widget(window5,"comboboxentry1");
if (f!=NULL)
{ while(fscanf(f,"%s %d %s %d %d %d %d %d\n",l.nom_liste,&l.id_liste,l.id_tete_liste,&l.nombre_condidat,&l.date.jour,&l.date.mois,&l.date.annee,&l.nbr_vote)!=EOF)
{ 

 gtk_combo_box_append_text(GTK_COMBO_BOX(comb),l.nom_liste);
}
}

}






// Ouvre la fenetre main 
void
on_main_liste_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *main;
  GtkWidget *window2;
  window2=lookup_widget(objet,"window2");
  main=lookup_widget(objet,"Main");
 main=create_Main();
 gtk_widget_show(main);
 gtk_widget_hide(window2);
 
}



// treeview condidat (window3)
void
on_treecond_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
  GtkTreeIter iter;
gchar *Nom;
gchar *Prenom;
gchar *CIN;


condidat l;

GtkTreeModel *model =gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)){
gtk_tree_model_get(GTK_LIST_STORE(model), &iter,0,&Nom,1,&Prenom,2,&CIN,-1);

afficher_condidat(treeview,  idl);


}

}









// modifier une liste (redirige vers window1)
void
on_modif_liste_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window1;
 GtkWidget *window3;
 GtkWidget *nom;
 GtkWidget *id_tete;
 GtkWidget *jour;
 GtkWidget *mois;
 GtkWidget *annee; 
 GtkWidget *noi; 
 GtkWidget *label;
 char noml[20];
liste l;
 test=1;
 window3=lookup_widget(objet,"window3");
 window1=lookup_widget(objet,"window1");
 window1=create_window1();
 gtk_widget_show(window1);
 label=lookup_widget(window1,"label2");
 gtk_widget_hide(window3);
 nom=lookup_widget(window1,"nom_liste");
 id_tete=lookup_widget(window1,"id_teteliste");
 jour=lookup_widget(window1,"jour");
 mois=lookup_widget(window1,"mois");
 annee=lookup_widget(window1,"annee");
 // Remplir les entry avec les information
 noi=lookup_widget(window3,"noi");
 strcpy(noml,gtk_label_get_text(noi));
 l=recherche_liste(noml);
 if (l.id_liste!=-1){
 gtk_entry_set_text(nom,l.nom_liste);
 gtk_entry_set_text(id_tete,l.id_tete_liste);
 gtk_spin_button_set_value(jour,l.date.jour);
 gtk_spin_button_set_value(mois,l.date.mois);
 gtk_spin_button_set_value(annee,l.date.annee);
 ida=l.id_liste;
 gtk_label_set_text(label,"Modifier la liste");

}
gtk_widget_hide(window3);


}










//Suprimer la liste 
void
on_button3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *nom;
  GtkWidget *window2;
 GtkWidget *window3;
 
  GtkTreeView *tree;
 char noml[20];
 int tr;
 liste l;
 window2=lookup_widget(objet,"window2");
 window3=lookup_widget(objet,"window3");

 nom=lookup_widget(objet,"noi");
 window2=create_window2();
 tree=lookup_widget(window2,"treels");
 strcpy(noml,gtk_label_get_text(nom));
 l=recherche_liste(noml);
 if( l.id_liste!=-1){
  tr=supprime_liste(l.id_liste);
}
afficher_liste(tree);
gtk_widget_hide(window3);
 
 
}















// ajouter un condidat (window4)
void
on_ajout_cond_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *window4;
 GtkWidget *nom;
 GtkWidget *prenom;
 GtkWidget *cin;
 GtkWidget *label;
 char id[12],NOM[30],PRENOM[30],CIN[12];
 int i;

 sprintf(id,"%d",ida);
 window4=lookup_widget(objet,"window4");
 nom=lookup_widget (window4,"nom_cond");
 prenom=lookup_widget(window4,"prenom_cond");
 cin=lookup_widget(window4,"CIN_cond");
 label=lookup_widget(window4,"lid_liste");
 strcpy(CIN,gtk_entry_get_text(GTK_ENTRY(cin)));
 
 if((strlen(CIN)>8)|(strlen(CIN)<8)){ gtk_label_set_text(GTK_LABEL(label),"Ecrire un CIN de 8 chiffre");}
 else {
 strcpy(PRENOM,gtk_entry_get_text(GTK_ENTRY(prenom)));
 strcpy(NOM,gtk_entry_get_text(GTK_ENTRY(nom)));
// nom du fichier txt user
 fflush(stdin);
 i=ajout_cond(NOM,PRENOM,CIN, ida);
if(i==1){
 gtk_widget_hide(window4);}}

}

// voter une liste (window5)
void
on_vote2_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window5;
 GtkWidget *comb;
 liste l;
 
 char nom [30];
 window5=lookup_widget(objet,"window5");
 comb=lookup_widget(window5,"comboboxentry1");
 strcpy(nom,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comb)));
 
l=recherche_liste(nom);
voter(l);
gtk_widget_hide(window5);

 }




// retour vers l'affichages des listes
void
on_Return_liste_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window2;
 GtkWidget *window6;
 window2=lookup_widget(objet,"window2");
 window6=lookup_widget(objet,"window6");
 window2=create_window2();
 gtk_widget_show(window2);
 window6=create_window6();
 gtk_widget_hide(window6);
}











// Affiche la fenetre 2 des listes 
void
on_listes_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *window2;
 GtkWidget *main;
 GtkTreeView *tree;
 window2=lookup_widget(objet,"window2");
 window2=create_window2();
 gtk_widget_show(window2);
 tree=lookup_widget(window2,"treels");
 
 afficher_liste(tree);
 main=lookup_widget(objet,"Main");
 
 gtk_widget_hide(main);
}

