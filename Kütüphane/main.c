#include <stdio.h>
#include <string.h>
#include <conio.h>


char key;
char ykitap[40];
FILE *dosya, *kdosya;
int islendi=0, kira=0, iade=0,baskasinda=0;
fpos_t position;

struct Kitap
{
char kitapAdi[40];
char yazar[20];
char durumu[10];
}kitap;

struct User
{
char userName[10];
char userLastname[20];
char odunc[40];
}user;

struct Kitap *p;
struct User *u;

int main (void)
{
    void Ekle(void);
    void Ara(char aranan[32]);
    void Kirala(void);
    void Iade(void);
    p=&kitap;
    u=&user;
    do
    {
            printf("\n\n****************************");
            printf("\n*****KUTUPHANE PROGRAMI*****");
            printf("\n* 1. Kitap Ekle *");
            printf("\n* 2. Kitap Ara *");
            printf("\n* 3. Kitap Kirala *");
            printf("\n* 4. Kitap iade *");
            printf("\n* 5. Exit *");
            printf("\n****************************\n");
            printf("\nSecim Yapin: ");
            key=getch();
            switch(key)
            {
                       case '1': Ekle(); break;
                       case '2':
                       {
                            printf("\n* Kitap Ara *");
                            printf("\nAranacak kitap adi: ");
                            gets(ykitap);
                            Ara(ykitap);
                            break;
                       }
                       case '3': Kirala(); break;
                       case '4': Iade(); break;
                       case '5': return 0;
            }
    }
    while(1);
}

void Ekle(void)
{
     printf("\n* Kitap Ekle *");
     dosya=fopen("book.txt","ab");
     printf("\nKitap adi: ");
     gets(p->kitapAdi);
     printf("\nYazar: ");
     gets(p->yazar);
     sprintf(p->durumu,"Serbest");
     fwrite(p,sizeof(kitap),1,dosya);
     p=&kitap;
     fclose(dosya);
}

void Ara(char aranan[40])
{
     dosya=fopen("book.txt","rb");
     fseek(dosya,0L,SEEK_SET);
     while(fread(p,sizeof(kitap),1,dosya)==1)
     {
           if(!strcmp(aranan,p->kitapAdi))
           {
                    fgetpos (dosya, &position);
                    printf("\nKitap adi:");
                    printf(" %s",p->kitapAdi);
                    printf("\nYazar:");
                    printf(" %s",p->yazar);
                    printf("\nDurumu:");
                    printf(" %s\n",p->durumu);
                    islendi=1;
                    fclose(dosya);
                    if(kira==1)
                    {
                               dosya=fopen("book.txt","rb+");
                               fsetpos (dosya,&position);
                               fseek(dosya,-10L,SEEK_CUR);
                               if(!strcmp(p->durumu,"Kirada"))
                               {
                                        printf("Kitap baskasi tarafindan kiralanmis.");
                                        baskasinda=1;
                                        break;
                               }
                               else
                               {
                                   printf("\n%s kitabi kiralandi.",p->kitapAdi);
                                   sprintf(p->durumu,"Kirada");
                                   printf("\nDurumu:");
                                   printf(" %s\n",p->durumu);
                                   fwrite(p->durumu,sizeof(kitap.durumu),1,dosya);
                                   fclose(dosya);
                                   break;
                               }
                    }
                    if(iade==1)
                    {        
                      dosya=fopen("borrow.txt","rb+");
                      fsetpos (dosya, &position);
                      printf("\n%s kitabi iade edildi.",p->kitapAdi);
                      sprintf(p->durumu,"Serbest");
                      printf("\nDurumu:");
                      printf(" %s\n",p->durumu);
                      fseek(dosya,-10L,SEEK_CUR);
                      fwrite(p->durumu,sizeof(kitap.durumu),1,dosya);
                      fclose(dosya);
                      break;
                    }
                    break;
           }              
     }
     if(islendi!=1)
     {
                   printf("\nKitap kayitli degil.");
                   baskasinda=1;
                   fclose(dosya);
     }
}

void Kirala(void)
{
     printf("\n* Kitap Kirala *");
     printf("\nKiralanacak Kitap: ");
     gets(u->odunc);
     kira=1;
     fclose(kdosya);
     islendi=0;
     Ara(u->odunc);
     if(baskasinda!=1)
     {
                      printf("\nKiralayanin Adi: ");
                      gets(u->userName);
                      printf("\nKiralayanin Soyadi: ");
                      gets(u->userLastname);
                      kdosya=fopen("c:\\user.txt","ab");
                      fwrite(u,sizeof(user),1,kdosya);
     }
     baskasinda=0;
     kira=0;
     fclose(kdosya);
}

void Iade(void)
{
     printf("\nIade edilecek kitap: ");
     gets(u->odunc);
     iade=1;
     islendi=0;
     Ara(u->odunc);
     printf("\n* Kitap iade *");
     kdosya=fopen("c:\\user.txt","rb+");
     fprintf(kdosya,"",u->odunc);
     iade=0;
     fclose(kdosya);
} 
