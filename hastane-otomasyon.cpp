#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct hasta
{
	char tc[20];
	char ad[20];
	char soyad[20];
	char tel[20];
	char adres[20];
	int klinikNo;
	int doktorNo;
	int durum;
};
struct doktor
{
	char ad[20];
	char soyad[20];
	int klinikNo;
	int doktorNo;
};

void hastaKayit()
{
	system("cls");
	struct hasta h1;
	struct doktor d1;
	int sonuc=0;
	printf("Hasta kayit ekrani\n");
	printf("TC    : "); scanf("%d",h1.tc);
	printf("AD    : "); scanf("%s",h1.ad);
	printf("SOYAD    : "); scanf("%s",h1.soyad);
	printf("GSM      : "); scanf("%d",h1.tel);
	printf("ADRES    : "); scanf("%s",h1.adres);
	
	system("cls");
	printf("Klinikler: 1-KBB ,2-Fizik ,3-Cocuk ,4-Noroloji ,5-Dahiliye \n");
	printf("KLINIK NO:"); scanf("%d", &h1.klinikNo );
	
	FILE *ptr=fopen("doktorlar.txt","r+b");
	
	 while( fread ( &d1, sizeof(struct doktor), 1, ptr ) !=NULL )
    {
    	if( h1.klinikNo == d1.klinikNo)
    	{
    		sonuc=1;
    		printf("%d\t%s\t%s\n",d1.doktorNo,d1.ad, strupr(d1.soyad ) );
		}
	}
	fclose(ptr);
	if(sonuc==0)
	{
	printf("Bu bolumun doktoru yok !\n ");
    }
	else
	{
		printf("DOKTOR NO : "); scanf("%d", &h1.doktorNo );
		h1.durum=0;
		FILE *hPtr = fopen("hastalar.txt","a+b");
		fwrite( &h1, sizeof(struct hasta),1, hPtr);
		fclose(hPtr);
		printf("Hasta kaydi tamamlanmistir.\n");
	}
}
void muayeneEt( struct doktor d1)
{
	system("cls");
	struct hasta h1;
	int sonuc=0,sayac=0;
	char aciklama[50];
	char dosyaAdi[6];
	dosyaAdi[0] = d1.ad[0];
	dosyaAdi[1] = d1.soyad[0];
	dosyaAdi[2] ='.';
	dosyaAdi[3] ='t';
	dosyaAdi[4] ='x';
	dosyaAdi[5] ='t';
	
	
	FILE *mPtr = fopen( dosyaAdi, "a");
	printf("\nBekleyen Hastalar\n\n");
	FILE *ptr=fopen("hastalar.txt", "r+b");
	while( fread ( &h1,sizeof(struct hasta ), 1, ptr) !=NULL )
	{
		if( d1.doktorNo == h1.doktorNo && h1.durum == 0)
		{
			sonuc=1;
			printf("%s hastasinin muayene sonucu :", h1.ad ); scanf("%s", aciklama );
			h1.durum=1;
			fprintf(mPtr, "%s\t%s\t%s%s\n", h1.tc,h1.ad,h1.soyad,aciklama );
			fclose(mPtr);
			
			fseek( ptr,(sayac) *sizeof(struct hasta),SEEK_SET);
			
			fwrite( &h1, sizeof(struct hasta),1,ptr);
			fclose(ptr);
			break;
		}
		sayac++;
	}
	fclose(ptr);
	if( sonuc==0)
	{
		printf("Bekleyen hastaniz kalmadi!\n");
	}
	else
	{
		muayeneEt(d1);
	}
}
void bekleyenHastalar( struct doktor d1)
{
	system("cls");
	struct hasta h1;
	int sonuc=0;
	
	printf("Bekleyen hastalara iliþkin ekran \n");
	
	FILE *ptr=fopen("hastalar.txt", "r+b");
	while( fread ( &h1, sizeof(struct hasta ), 1, ptr ) !=NULL )
	{
		if( d1.doktorNo == h1.doktorNo && h1.durum ==0 )
		{
			sonuc=1;
			printf("%s\t%s\t%s \n",h1.tc, h1.ad, strupr(h1.soyad));
		}
	}
	fclose(ptr);
	if( sonuc==0 )
	{
		printf("Bekleyen hastaniz yoktur. \n");
	}
	else
	{
		muayeneEt(d1);
	}
}
void doktorGiris()
{
	system("cls");
	struct doktor d1;
	char kullaniciAdi[20], parola[20];
	int sonuc=0;
	
	printf("Doktor giris ekrani \n");
	printf("Kullanici adi   : "); scanf("%s", kullaniciAdi);
	printf("Parola          :  "); scanf("%s", parola);
	
	FILE *ptr=fopen("doktorlar.txt","r+b");
    while( fread ( &d1, sizeof(struct doktor), 1, ptr ) !=NULL )
    {
    	if( strcmp( kullaniciAdi, d1.ad ) ==0 && strcmp( parola, d1.soyad) ==0)
    	{
    		sonuc=1;
    		printf("Dr. %s %s Hos Geldiniz ...\n",d1.ad, strupr(d1.soyad ) );
    		break;
		}
	}
	fclose(ptr);
	if( sonuc==0)
	{
		printf("Hatali Kullanici adi veya parola!\n");
	}
	else
	{
		bekleyenHastalar(d1);
	}
}
void doktorKayit()
{
	system("cls");
	struct doktor d1;
	
	printf("Doktor kayit ekrani \n");
	printf("AD    : "); scanf("%s", d1.ad);
	printf("SOYAD :  "); scanf("%s", d1.soyad);
	system("cls");
	printf("Klinikler: 1-KBB ,2-Fizik ,3-Cocuk ,4-Noroloji ,5-Dahiliye \n");
	printf("KLINIK NO:"); scanf("%d", &d1.klinikNo );
	printf("DOKTOR NO: "); scanf("%d", &d1.doktorNo );
	
	FILE *ptr=fopen("doktorlar.txt","a+b");
	fwrite( &d1,sizeof(struct doktor), 1, ptr );
	fclose(ptr);
	printf("Doktor kaydi tamamlanmistir.\n");
	
}
void doktorListe()
{
	system("cls");
	struct doktor d1;
	int adet=0;
	
	printf("%s\t%s\t%s\t%s\n","kNo","dNo","AD","SOYAD");
	
	FILE *ptr=fopen("doktorlar.txt","r+b");
	while( fread ( &d1,sizeof(struct doktor), 1,ptr ) !=NULL )
	{
		adet++;
		printf("%d\t%d\t%s\t%s\n",d1.klinikNo,d1.doktorNo,d1.ad,d1.soyad);
	}
	fclose(ptr);
	printf("Doktor sayisi: %d", adet);
}
int menu()
{
	int secim;
	printf("\nHASTANE OTOMASYONU \n\n");
	printf("1- Hasta Kayit \n");
	printf("2- Doktorlari Listele\n");
	printf("3- Doktor Giris \n");
	printf("4- Doktor Kayit \n");
	printf("0- Programi Kapat \n");
	printf("Seciminiz: ");
	scanf("%d",&secim);
	return secim;
}
int main()
{
	int secim= menu();
	while( secim != 0)
	{
		switch(secim)
		{
			case 1: hastaKayit(); break;
			case 2: doktorListe(); break;
			case 3: doktorGiris(); break;
			case 4: doktorKayit(); break;
			case 0: break;
			default : printf("Hatali secim ! \n");break;
		}
		secim = menu();
	}
	
	return 0;
}
