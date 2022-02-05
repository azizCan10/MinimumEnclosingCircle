#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int x[20];				//x koordinatlarý bu diziye atanacak
int y[20];				//y koordinatlarý bu diziye atanacak
int i, n, j;
double X = 0, Y = 0;	//x ve y koordinatlarý her okunduðunda bu deðiþkenlere eklenecek
double uzaklik, uzaklik2, r;
int a, b = 20;

void dosya_acma_koordinatlari_okuma()
{
	char *kontrol;
	char str[100];
	FILE *dosya;
	dosya = fopen("C:\\Users\\JAN\\Desktop\\koordinat.txt", "r");		//dosya okuma modunda açýldý
	fscanf(dosya, "%s", str);				//dosyadan okuma
	kontrol = strtok(str, ",");				//ilk virgülü görene kadar olan kýsmý okuyup kontrole atadý ve virgülü atladý

	i = 0;
	while (kontrol != NULL)			
	{
    	x[i] = atoi(kontrol);				//kontrole atanan array i, int e çevirip x[i] ye atadý
   		kontrol = strtok(NULL, ",");		//Bir sonraki virgüle e kadar olan kýsmý alýp kontrole e atadý
   		X += x[i];
   		
   	 	y[i] = atoi(kontrol);	 			//kontrole atanan array i, int e çevirip y[i] ye atadý
   	 	kontrol = strtok(NULL, ",");		//Bir sonraki virgüle e kadar olan kýsmý alýp kontrole e atadý
		Y += y[i];
		
   		i++;		
	}
	
	n = i;								//n koordinat sayýsýna eþit oldu
	fclose(dosya);						//dosya kapandý
}

void konsola_koordinat_yazma()
{
	for (i = 0; i < n; i++)							//koordinatlarý konsola yazdýrdý
  	  printf("%3d , %3d\n", x[i], y[i]);			
}

void cember_merkez_yaricap()
{
	X /= n;										//x koordinatlarý toplamýný koordinat sayýsýna böldü
  	Y /= n;										//y koordinatlarý toplamýný koordinat sayýsýna böldü
  	double kontrol_degiskeni = 0.1;
  	
  	for (i = 0; i < 10000; i++)							//Sonuca daha çok yakýnlaþmasý için 10000 kere çalýþtýrýldý
 	{
  		int f = 0;
    	uzaklik = (X - x[0])*(X - x[0]) + (Y - y[0])*(Y - y[0]);	//X,Y koordinatýnýn diðer noktalarla olan uzaklýðý karþýlaþtýrýlmak üzere baslangýç uzaklýðý seçildi
    	
    	for (j = 1; j < n; j++)
   		{
    		uzaklik2 = (X - x[j])*(X - x[j]) + (Y - y[j])*(Y - y[j]);		//Uzaklýk deðiþkeni ile karþýlaþtýrýlmak üzere bir sonraki noktayla olan uzaklýk hesaplandý
    		
     		if (uzaklik < uzaklik2)
      		{
      			uzaklik = uzaklik2;
      			f = j;										//Uzaklýðý fazla olan noktanýn indisi f ye atandý.
     		}
   		}
   		
   		X += (x[f] - X) * kontrol_degiskeni;				//f indisindeki x,y koordinatý X,Y koordinatýna kontrol degiskeni oranýnda yakýnlastý.
   		Y += (y[f] - Y) * kontrol_degiskeni;
   		kontrol_degiskeni *= 0.999;							//Her döngüde çemberin merkezine yakýnlaþan koodinatýn yakýnlaþma oraný küçüldü.Limit gibi
 	}	
 	
 	r = sqrt(uzaklik);										//Uzaklýðýn karekökü alýndý ve r ye atandý.
}

void konsola_yaricap_merkez_yazdirma()					//merkez ve yarýçapý konsola yazdýrdý
{
 	printf("Merkez = {%.3lf, %.3lf}\n", X, Y);
 	printf("Yaricap = %.3lf", r); 
}

void koordinat_sistemi()
{	
	initwindow(831, 841);			//800x800 lük pencere açtýk, x ten 11 birim y den 21 birim eksik açtýðý için 811 e 822 lik açtýk, 20 birim de grafiðin dýþýna boþluk olmasý için
	line(400, 0, 400, 800);			//y düzlemini çizdirdi
	line(0, 400, 800, 400);			//x düzlemini çizdirdi
	
	int cizik;
	setcolor(8);
	for (cizik = 0; cizik < 41; cizik++)			
	{					
		if (cizik == 20)
			continue;
		line(0+20*cizik, 0, 0+20*cizik, 820);       //x koordinatlarý için boydan boya çizgiler çizdirdi
		line(0, 0+20*cizik, 820, 0+20*cizik);		//y koordinatlarý için boydan boya çizgiler çizdirdi
	}

	setcolor(15);
	char sayi[20];
	for (a = -20; a <= 20; a++)						//koordinat sistemine x deðerlerini girdirdi
	{
		if (a == 0)
		{
			b--;
			continue;
		}
		sprintf(sayi, "%d", a);
		settextstyle(SMALL_FONT, 0, 5);				//yazý fontunu, yönünü ve boyutunu ayarladý
		outtextxy(0+ (20-b)*20, 405, sayi);			//koordinatý ve girilecek yazýyý ayarladý
		b--;
	} 
	
	char sayi2[20];
	b = 20;
	for (a = 20; a >= -20; a--)						//koordinat sistemine y deðerlerini girdirdi
	{
		if (a == 0)
		{
			b--;
			continue;
		}
		sprintf(sayi2, "%d", a);
		settextstyle(SMALL_FONT, 0, 5);				//yazý fontunu, yönünü ve boyutunu ayarladý
		outtextxy(405, 0+ (20-b)*20, sayi2);		//koordinatý ve girilecek yazýyý ayarladý
		b--;
	}
	
	for (cizik = 0; cizik < 41; cizik++)					//x koordinatlarýna çizik attýrdý
		line(0+20*cizik, 397, 0+20*cizik, 403); 
		
	for (cizik = 0; cizik < 41; cizik++)					//y koordinatlarýna çizik attýrdý
		line(397, 0+ 20*cizik, 403, 0+ 20*cizik);
}

void cember_cizimi()
{
	setcolor(3);
	circle(400+ X*20, 400-Y*20, r*20);				//elde edilen merkeze ve yarýçapa göre daireyi çizdirdi
	
	for (i = 0; i < n; i++)								//girilen noktalarý ekrana çizdirdi
	{
		setcolor(4);
		setfillstyle(SOLID_FILL, 4);				//içini doldurdu ve rengini belirledi
		fillellipse(400+ 20*x[i], 400-20*y[i], 5, 5);	//x y koordinatý ve x y yarýçapýný ayarladý
	}
	
	{
		setcolor(14);									//yarýçapý çizdirdi
		setfillstyle(SOLID_FILL, 14);					//içini doldurdu ve boyutunu belirledi
		fillellipse(400+X*20, 400-Y*20, 5, 5);			//içi dolu bir þekilde merkezi çizdi
		line(400+X*20, 400-Y*20, 400+X*20+r*20, 400-Y*20);	//yarýçapý çizdi
	}
}

void grafige_yaricap_merkez_yazdirma()
{
	setcolor(10);
	settextstyle(SMALL_FONT, 0, 7);
	outtextxy(20, 20, "Yaricap: ");			//verilen koordinatlara Yarýçap: yazdýrdý			
	outtextxy(20, 50, "Merkez: ");			//verilen koordinatlara Merkez: yazdýrdý
	
	setcolor(15);
	char yaricap[10];
	char koordinat_x[10];
	char koordinat_y[10];
	sprintf(yaricap, "%lf", r);
	outtextxy(90, 20, yaricap);				//verilen koordinatlara yarýçapýn deðerini yazdýrdý
	
	sprintf(koordinat_x, "%.2lf", X);
	outtextxy(90, 50, koordinat_x);			//verilen koordinatlara merkezin x noktasýný yazdýrdý
	
	outtextxy(130, 50, ",");				//verilen koordinatlara x ve y arasýna virgül koydu
	
	sprintf(koordinat_y, "%.2lf", Y);
	outtextxy(140, 50, koordinat_y);		//verilen koordinatlara merkezin y noktasýný yazdýrdý
}

int main()
{
    dosya_acma_koordinatlari_okuma();
    konsola_koordinat_yazma();
    cember_merkez_yaricap();
	konsola_yaricap_merkez_yazdirma();
	koordinat_sistemi();
	cember_cizimi();
	grafige_yaricap_merkez_yazdirma();
	
	getch();
	closegraph();
	return 0;
}
