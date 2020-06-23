#define _CRT_SECURE_NO_WARNINGS							//c foksiyonlar� kullan�rken hata vermemesi i�in yazd���m bir sat�r

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

#include<stdio.h>
#include<stdlib.h>

using namespace std;

void tabloyuolustur(FILE& dama, FILE& turlar);
void yazdir(FILE& dama);
void tarama(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur);
bool komutal(string* tur, string* komut);
bool pulhareketi(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur, string* komut, string yemehar[50], string yenileny[50]);
void yazdir(FILE& dama);
void donusum(FILE& dama);
bool yemekontrolu(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur, string yemehar[50], string yenileny[50]);
void turdegis(FILE& dama);
bool turdevami(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur, string yemehar[50], string yenileny[50], string* komut, string* k1, string* k2, FILE& turlar);
void turlarikaydet(FILE& dama, FILE& turlar, string* komut);

int main() {
	int sec = 0, i = 0;										//burada bir�ok tan�mlama yapt�m ve pointer ile fonksiyonlara g�nderdim ki
	string tur, k1, k2;										//ayn� de�i�kenleri bir�ok fonksiyonda kullanabileyim diye
	FILE* dama;
	FILE* turlar;
	dama = fopen("damaoyun.txt", "a");						//e�er dosya yoksa olu�turmas� i�in
	fclose(dama);											//a ile a��yorum ki e�er dosya varsa silinmesin
	turlar = fopen("turlar.txt", "a");
	fclose(turlar);
	string s1[8], s2[8], s3[8], s4[8], s5[8], s6[8], s7[8], s8[8], yemehar[50], yenileny[50];		//kontroller i�in kullan�d���m diziler
	string komut;																					//ta�lar� dizilere al�yorum ki kontrol ederken
																									//daha verimli olsun
	while (sec != 3) {
		cout << "Komut Giriniz: \n";
		cout << "1)Yeni Oyun Olustur\n2)Devam Et\n3)Oyundan Cik(Herhangi Bir Zaman Kullanilabilir)\n";
		cin >> sec;
		system("CLS");
		switch (sec) {

		case 1:
			tabloyuolustur(*dama, *turlar);															//yeni oyun olu�turup se�im ekran�na d�nd�r�yorum
			tarama(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur);
			system("CLS");
			cout << "Yeni Oyun Olusturuldu\n\n";
			break;
		case 2:
			while (sec != 3) {																		//devam et istenild�inde kullan�labiliyor oyun yoksa �nce oyun a��lmal�
				tarama(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur);								//her oyun ba�� tarama ile ta�lar� dizilere koyuyorum
				yazdir(*dama);
				yemekontrolu(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, yemehar, yenileny);		//yeme kotrollerini kontrol ediyorum
				if (komutal(&tur, &komut) == 0) {													//komut 0 d�nd�r�yosa oyundan ��k�yorum
					sec = 3;
					break;
				}
				if ((pulhareketi(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, &komut, yemehar, yenileny)) == 0) {	//pul hareketi olmad�ysa hata mesaj� veriyorum
					system("CLS");
					cout << "Hatali Hamle\n";
				}
				else if ((pulhareketi(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, &komut, yemehar, yenileny)) == 1) {	//pul hareketi olduysa turlar� kay�t ediyorum
					turlarikaydet(*dama, *turlar, &komut);

					if ((turdevami(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, yemehar, yenileny, &komut, &k1, &k2, *turlar)) == 1) {}
					else {
						system("CLS");																									// e�er tur devam� yoksa turu de�i�tiriyorum
						turdegis(*dama);
					}
				}
				donusum(*dama);																			//en son sona ula�m�� ta� varsa BB yada SS ye d�n��t�r�yorum
				tarama(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur);
			}
			break;
		case 3:																			//komut verme s�ras�nda ��k�� yap�yor burda direkt se�im ekran�nda bas�l�rsa diye yapt�m
			break;
		default:
			cout << "Yanlis Tercih\n";
		}
	}
}
//a��klama sat�rlar�n� fonksiyonlar�n i�ine yerle�tirdim daha d�zenli olmas� ad�na	
void tabloyuolustur(FILE& dama, FILE& turlar) {
	fopen("damaoyun.txt", "w");															//dosyay� w ile a��yorum ki i�indeki t�m bilgiler silinsin
	fprintf(&dama,																		//yeni oyun olu�tururken bu fonksiyon ile dosyaya direkt ba�lang�� durumunu yaz�yorum
		"                           \n"
		"                           \n"
		"    b  b  b  b  b  b  b  b \n"
		"    b  b  b  b  b  b  b  b \n"
		"                           \n"
		"                           \n"
		"    s  s  s  s  s  s  s  s \n"
		"    s  s  s  s  s  s  s  s \n"
		"                           \n"
		"     b                     ");
	fclose(&turlar);																	// ayn� �ekilde turlar�da a��k kap�yorum w ile b�ylece yeni oyun olu�turuldu�unda di�er oyunun verileri silinsin
	fopen("turlar.txt", "w");
	fclose(&turlar);
}

void yazdir(FILE& dama) {
	int a = 33, k, i;														//oyun konsol ekran�ndan oynand��� i�in dosyadaki veri bulunabilecek yerleri se�ip hepsini diziye at�yorum
	int m = 0;															//sonrada ekrana yazd�r�yorum
	char line[128];
	fopen("damaoyun.txt", "r");

	for (i = 0; i < 8; i++) {
		for (k = 0; k < 8; k++) {
			fseek(&dama, 33 + 3 * k + 29 * i, SEEK_SET);
			line[m] = fgetc(&dama);
			m++;
			fseek(&dama, (33 + 3 * k + 29 * i) - 1, SEEK_SET);
			line[m] = fgetc(&dama);
			m++;
		}
	}
	printf("   a  b  c  d  e  f  g  h  \n");
	for (i = 1, m = 0; i < 9; i++, m = m + 16) {
		printf("%d |%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|\n", i, line[m], line[m + 1], line[m + 2], line[m + 3], line[m + 4], line[m + 5], line[m + 6], line[m + 7], line[m + 8], line[m + 9], line[m + 10], line[m + 11], line[m + 12], line[m + 13], line[m + 14], line[m + 15]);
	}
	fclose(&dama);
}

void tarama(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur) {
	int i, k, a = 33, s = 5;
	string c;												//bu fonksiyon sayesinde oyunda yeri de�i�en ta� oldu�u an dizideki yerinide de�i�tiriyorum
	fopen("damaoyun.txt", "r+");							//b�ylece kontrolleri yaparken diziler �st�nden kullanabileyim
	string* diziler[8] = { s1,s2,s3,s4,s5,s6,s7,s8 };		//ayn� zamanda oyuna devam edildi�i zaman ta�lar� dizilere �ekiyorum ki oyuna devam edilebilsin

	for (i = 0; i < 8; i++) {
		for (k = 0; k < 8; k++) {							//a1=33,a2=62,a3=91,a4=120,a5=149,a6=178,a7=207,a8=236;
			fseek(&dama, a, SEEK_SET);							//her bir ta� aras�nda 3 bo�luk var bu y�zden 3 ekliyorum
			c = fgetc(&dama);									//her 8 s�t�nu okuduktan sonra a�a��daki ilk s�t�na varabilmesi i�inse 5 ekliyorum
			diziler[i][k] = c;
			a = a + 3;
		}
		a = a + s;
	}

	fseek(&dama, 266, SEEK_SET);							//burda da turun kimde oldu�u bilgisini tutup di�er fonksiyonlarda kullanmak �zere
	c = fgetc(&dama);										//g�nderiyorum
	*tur = c;

	fclose(&dama);
}

bool komutal(string* tur, string* komut) {
	string a;
	char ar[100];
	if (*tur == "b")
		cout << "Beyaz Hareket Gir:";						//e�er tur de�i�keninde b varsa beyaz i�in komut istiyorum
	else {													//e�er tur de�i�keninde s varsa siyah i�in komut istiyorum
		cout << "Siyah Hareket Gir:";
	}

	cin >> a;												//komutu al�yorum



	strcpy(ar, a.c_str());									//ald���m stringi char dizisine at�yorum ki kontrol edebileyim

	if (a == "3") {											//komut verme s�ras�nda 3 e bas�l�rsa oyundan ��k�lmas� i�in kontrol ediyorum
		return 0;
	}

	for (; a.length() != 4;) {								//string uzunlu�u 4 ten b�y�kse hatal� hamle oldu�unu ekrana yazd�r�p birdaha al�yorum
		cout << "Hatali Hamle Tekrar Giriniz\n";			//bunu try i�inde yapmam�n sebebi baz� girdiler sonucu program�n kapanmas�
		try {
			cin >> a;
		}
		catch (exception e) {
		}
	}

	if (ar[0] == 'a' || ar[0] == 'b' || ar[0] == 'c' || ar[0] == 'd' || ar[0] == 'e' || ar[0] == 'f' || ar[0] == 'g' || ar[0] == 'h') {
		if (ar[1] == '1' || ar[1] == '2' || ar[1] == '3' || ar[1] == '4' || ar[1] == '5' || ar[1] == '6' || ar[1] == '7' || ar[1] == '8') {
			if (ar[2] == 'a' || ar[2] == 'b' || ar[2] == 'c' || ar[2] == 'd' || ar[2] == 'e' || ar[2] == 'f' || ar[2] == 'g' || ar[2] == 'h') {
				if (ar[3] == '1' || ar[3] == '2' || ar[3] == '3' || ar[3] == '4' || ar[3] == '5' || ar[3] == '6' || ar[3] == '7' || ar[3] == '8') {
					string komutt(ar);										//e�er char dizisi istenen formattaysa komut al�n�yor ve stringe geri d�n��t�r�l�yor
					*komut = komutt;
					return 1;
				}
				else { system("CLS"); cout << "Yanlis Komut Tekrar Giriniz\n"; }

			}
			else { system("CLS"); cout << "Yanlis Komut Tekrar Giriniz\n"; }
		}
		else { system("CLS"); cout << "Yanlis Komut Tekrar Giriniz\n"; }

	}
	else { system("CLS"); cout << "Yanlis Komut Tekrar Giriniz\n"; }
	return 1;
}

bool pulhareketi(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur, string* komut, string yemehar[50], string yenileny[50]) {
	string komutt = *komut;
	int a = 33, i;
	char t = 0, b = 0, l;
	char ar[100];
	strcpy(ar, komutt.c_str());
	char ar2[100], ar3[100];
	string* diziler[8] = { s1,s2,s3,s4,s5,s6,s7,s8 };
	string hareket, yok;
	hareket = "";
	yok = "";

	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 1) {			//Bu if kontrolule hareket s�ras�nda yeme zorunlulu�u varsa
		for (i = 0; i < 50; i++) {																	//yeme hamlesi yap�lmas� i�in zorluyorum
			if (*komut == yemehar[i]) {																//bu de�i�kenleri daha a�a��daki bir fonksiyondan al�yorum								
				hareket = yemehar[i];																//e�er komut yeme yap�lmas� i�in gereken hareketle aym� ise de�i�kene ata
				yok = yenileny[i];																	//yenilecek ta��n pozisyonunu de�i�kene ata
				break;
			}
		}
		if (hareket != *komut) {
			system("CLS");																			//e�er komut herhangi bir yeme hareketiyle e�it de�ilse yeme zorunlulu�u oldu�u i�in
			cout << "Hatali Hamle Yemen Gerekiyor\n";												//hata ver
			return 0;
		}
		strcpy(ar2, hareket.c_str());																//ald���m�z de�i�kenleri char dizilerine at�yorum ki kontrol edebilmek i�in
		strcpy(ar3, yok.c_str());

		if (*tur == "b") {																			//tur beyaz�nsa
			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "b") {								//se�ilen ta� b ise
				fopen("damaoyun.txt", "r+");
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);			//yedi�i ta�� al
				l = fgetc(&dama);
				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97), SEEK_SET);			//gidece�i yere b yaz
				fputs("b", &dama);
				fseek(&dama, 33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97), SEEK_SET);			//daha �nce oldu�u yeri ve yedi�i ta� yerine " " yaz
				fputs(" ", &dama);
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				if (l == 'S') {
					fseek(&dama, (33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97)) - 1, SEEK_SET);	//e�er yenen ta� S ise bir �nceki noktay�da sil ��nk� damalar SS diye dosyaya yaz�l�
					fputs(" ", &dama);
				}
				fclose(&dama);
				return 1;
			}

			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "B") {					//ayn� durumlar ayn� �ekilde di�er yeme hareketleri i�inde ge�eli
				fopen("damaoyun.txt", "r+");											//beyaz dama yani B i�in
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				l = fgetc(&dama);

				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97), SEEK_SET);
				fputs("B", &dama);
				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97) - 1, SEEK_SET);
				fputs("B", &dama);
				fseek(&dama, 33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				fseek(&dama, (33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97)) - 1, SEEK_SET);
				fputs(" ", &dama);
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				if (l == 'S') {
					fseek(&dama, (33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97)) - 1, SEEK_SET);
					fputs(" ", &dama);
				}
				fclose(&dama);
				return 1;
			}
		}
		if (*tur == "s") {
			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "s") {					//s ta�lar i�in
				fopen("damaoyun.txt", "r+");
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				l = fgetc(&dama);

				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97), SEEK_SET);
				fputs("s", &dama);
				fseek(&dama, 33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				if (l == 'B') {
					fseek(&dama, (33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97)) - 1, SEEK_SET);
					fputs(" ", &dama);
				}
				fclose(&dama);
				return 1;
			}
			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "S") {					//siyah dama yani S i�in
				fopen("damaoyun.txt", "r+");
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				l = fgetc(&dama);

				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97), SEEK_SET);
				fputs("S", &dama);
				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97) - 1, SEEK_SET);
				fputs("S", &dama);
				fseek(&dama, 33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				fseek(&dama, (33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97)) - 1, SEEK_SET);
				fputs(" ", &dama);
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				if (l == 'B') {
					fseek(&dama, (33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97)) - 1, SEEK_SET);
					fputs(" ", &dama);
				}
				fclose(&dama);
				return 1;
			}
		}
	}


	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 0) {								//bu k�s�m yeme zorunlulu�u olmayan hareketlerde ge�erli
		if (*tur == "b") {
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "b") {														//se�ilen ta� b ise ve pul hareketi a�a�� do�ruysa
				if ((abs(ar[0] - ar[2]) == 1 && abs(ar[1] - ar[3]) == 0)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }									//se�ilen yer bo�sa ��k
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }	//gidilecek yerde ta� varsa ��k
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);		//bu if komutlar�n� ge�erse
					fputs("b", &dama);																//gidilecek yere ta�� koy
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);																//�nceki oldu�u yerden ta�� sil
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "b") {			//se�ilen ta� b ise ve hareket sa�a yada sola do�ruysa
				if (abs(ar[0] - ar[2]) == 0 && (ar[3] - ar[1] == 1)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("b", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "B") {								//se�ilen ta� B ise ve hareket a�a�� yada yukar� do�ruysa
				if ((abs(ar[0] - ar[2]) < 8 && abs(ar[1] - ar[3]) == 0)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("B", &dama);
					fseek(&dama, (33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97)) - 1, SEEK_SET);
					fputs("B", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fseek(&dama, (33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97)) - 1, SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "B") {										//se�ilen ta� B ise ve hareket sa�a yada sola do�ruysa		
				if (abs(ar[0] - ar[2]) == 0 && (abs(ar[3] - ar[1]) < 8)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("B", &dama);
					fseek(&dama, (33 + ((29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97))) - 1, SEEK_SET);
					fputs("B", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fseek(&dama, (33 + ((29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97))) - 1, SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
		}


		if (*tur == "s") {
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "s") {						//se�ilen ta� s ise ve hareket yukar� do�ruysa
				if ((abs(ar[0] - ar[2]) == 1 && abs(ar[1] - ar[3]) == 0)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("s", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "s") {							//se�ilen ta� s ise ve hareket sa�a yada sola do�ruysa
				if (abs(ar[0] - ar[2]) == 0 && (ar[1] - ar[3] == 1)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("s", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "S") {														//se�ilen ta� S ise ve hareket yukar� yada a�a�� do�ruysa
				if ((abs(ar[0] - ar[2]) < 8 && abs(ar[1] - ar[3]) == 0)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("S", &dama);
					fseek(&dama, (33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97)) - 1, SEEK_SET);
					fputs("S", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fseek(&dama, (33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97)) - 1, SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "S") {											//se�ilen ta� S ise ve hareket sa�a yada sola do�ruysa
				if (abs(ar[0] - ar[2]) == 0 && (abs(ar[3] - ar[1]) < 8)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);
					fputs("S", &dama);
					fseek(&dama, (33 + ((29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97))) - 1, SEEK_SET);
					fputs("S", &dama);
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);
					fseek(&dama, (33 + ((29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97))) - 1, SEEK_SET);
					fputs(" ", &dama);
					fclose(&dama);
					return 1;
				}
			}
		}
	}
	system("CLS");
	cout << "Hatali Hamle\n";						//komut hi� bir harekete uymuyorsa yada hatal� bir komut girildiysa hata mesaj�
	return 0;
}

void donusum(FILE& dama) {
	int i = 0;
	char a;
	fopen("damaoyun.txt", "r+");
	for (i = 0; i < 8; i++) {										//t�m 8. s�tunu tar�yorum e�er beyaz ta� varsa damaya �eviriyorum
		fseek(&dama, 236 + 3 * i, SEEK_SET);						//238 8. s�tunun ba�lang�c�
		a = fgetc(&dama);
		if (a == 'b') {
			fseek(&dama, 236 + 3 * i, SEEK_SET);
			fputs("B", &dama);
			fseek(&dama, (236 + 3 * i) - 1, SEEK_SET);
			fputs("B", &dama);
		}
	}
	for (i = 0; i < 8; i++) {										//t�m 1. s�tunu tar�yorum e�er siyah ta� varsa damaya �eviriyorum
		fseek(&dama, 33 + 3 * i, SEEK_SET);							//33 1. s�tunun ba�lang�� karesini yeri ve 3 �n katlar�yla toplama sebebim
		a = fgetc(&dama);											// yan�ndaki s�t�n ondan 3 birim uzakta
		if (a == 's') {
			fseek(&dama, 33 + 3 * i, SEEK_SET);
			fputs("S", &dama);
			fseek(&dama, (33 + 3 * i) - 1, SEEK_SET);
			fputs("S", &dama);
		}
	}
	fclose(&dama);
}

bool yemekontrolu(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur, string yemehar[50], string yenileny[50]) {
	int i, k, p, r, s, t, u, v, y = 0, z = 0, m;
	string yiyen[50];
	string yiyen1[50];
	string yiyen2[50];
	string yiyen3[50];
	string yenilen[50];
	string yenilen1[50];
	string* diziler[8] = { s1,s2,s3,s4,s5,s6,s7,s8 };
	for (p = 0; p < 50; p++) {
		yiyen[p] = "";
		yiyen1[p] = "";
		yiyen2[p] = "";
		yiyen3[p] = "";
		yenilen[p] = "";
		yenilen1[p] = "";
	}

	p = 0;
	r = 0;
	s = 0;
	t = 0;
	u = 0;
	v = 0;

	if (*tur == "b") {									//tur beyaz�nsa
		for (i = 0; i < 8; i++) {
			for (k = 1; k < 6; k++) {					//beyaz ta��n a�a��s�nda yenebilecek ta� var m� diye kontrol ediyorum 2. sat�dan 6. sat�ra kadar kontrol var ��nk� beyaz bir ta� 7. sat�rdaysa ve 8. sat�rda bir siyah ta� varsa bunu yiyemez ve bi�bir normal beyaz ta� 1. sat�rda bulunamaz bu mant�kla di�er ta�lar i�inde kontorl yapt�m
				if (diziler[k][i] == "b" && (diziler[k + 1][i] == "s" || diziler[k + 1][i] == "S") && diziler[k + 2][i] == " ") {		//e�er komuttaki ta� b ise ve �n�nde S yada s varsa ve onlar�n alt�ndaki sat�r bo�sa devam et
					yiyen[p] = to_string(i);
					yiyen1[r] = to_string(k + 3);				//k lar� hep 1 le toplamam�n sebebi 1. sat�r�n 0. dizi olmas�
					yenilen[s] = to_string(i);
					yenilen1[t] = to_string(k + 2);
					yiyen2[u] = to_string(i);
					yiyen3[v] = to_string(k + 1);
					p++;
					r++;
					s++;
					t++;
					u++;
					v++;
				}
			}
		}
		for (i = 0; i < 6; i++) {								//beyaz ta�lar�n sa��ndaki ta�lar i�in yeme kontrolu
			for (k = 1; k < 7; k++) {							//ayn� �ekilde yaln�zca 1. s�tundan 6. s�tuna kadar kontrol var
				if (diziler[k][i] == "b" && (diziler[k][i + 1] == "s" || diziler[k][i + 1] == "S") && diziler[k][i + 2] == " ") {
					yiyen[p] = to_string(i + 2);
					yiyen1[r] = to_string(k + 1);
					yenilen[s] = to_string(i + 1);
					yenilen1[t] = to_string(k + 1);
					yiyen2[u] = to_string(i);
					yiyen3[v] = to_string(k + 1);
					p++;
					r++;
					s++;
					t++;
					u++;
					v++;
				}
			}
		}
		for (i = 2; i < 8; i++) {								//beyaz ta�lar�n solundaki ta�lar i�in yeme kontrolu
			for (k = 1; k < 7; k++) {							//ayn� �ekilde yaln�zca 8. s�tundan 3. s�tuna kadar kontrol var
				if (diziler[k][i] == "b" && (diziler[k][i - 1] == "s" || diziler[k][i - 1] == "S") && diziler[k][i - 2] == " ") {
					yiyen[p] = to_string(i - 2);
					yiyen1[r] = to_string(k + 1);
					yenilen[s] = to_string(i - 1);
					yenilen1[t] = to_string(k + 1);
					yiyen2[u] = to_string(i);
					yiyen3[v] = to_string(k + 1);
					p++;
					r++;
					s++;
					t++;
					u++;
					v++;
				}
			}
		}
		for (i = 0; i < 8; i++) {								//beyaz dama i�in kontoller
			for (k = 0; k < 6; k++) {							//bu kontrol daman�n alt�ndaki sat�rdaki ta�lara bakar e�er siyah ta� varsa ve ta��n arkas� bo�sa yeme hareketi olarak kaydeder
				for (m = 0; m < 7 - k; m++) {
					if (diziler[k][i] == "B" && (diziler[k + m][i] == "s" || diziler[k + m][i] == "S") && diziler[k + m + 1][i] == " ") {
						if ((diziler[k + m][i] == "s" || diziler[k + m][i] == "S") && (diziler[k + m - 1][i] == "s" || diziler[k + m - 1][i] == "S")) {
							continue;
						}
						yiyen[p] = to_string(i);
						yiyen1[r] = to_string(k + m + 2);
						yenilen[s] = to_string(i);
						yenilen1[t] = to_string(k + m + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}
		for (i = 0; i < 8; i++) {								//beyaz dama i�in kontoller
			for (k = 2; k < 8; k++) {							//bu kontrol daman�n �st�ndeki sat�rlardaki ta�lara bakar e�er siyah ta� varsa ve ta��n arkas� bo�sa yeme hareketi olarak kaydeder
				for (m = 0; m < k; m++) {
					if (diziler[k][i] == "B" && (diziler[k - m][i] == "s" || diziler[k - m][i] == "S") && diziler[k - m - 1][i] == " ") {
						if ((diziler[k - m][i] == "s" || diziler[k - m][i] == "S") && (diziler[k - m + 1][i] == "s" || diziler[k - m + 1][i] == "S")) {
							continue;
						}
						yiyen[p] = to_string(i);
						yiyen1[r] = to_string(k - m);
						yenilen[s] = to_string(i);
						yenilen1[t] = to_string(k - m + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						for (int c = 0; c < 8 - k; c++) {
							if (diziler[k - m - c][i] == " ") {
								yiyen[p] = to_string(i);
								yiyen1[r] = to_string(k - c);
								p++;
								r++;
								if (diziler[k - m - c][i] != " ") {
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
		for (i = 0; i < 6; i++) {								//beyaz dama i�in kontoller
			for (k = 0; k < 8; k++) {							//bu kontrol daman�n sa� taraf�dndaki s�t�nlardaki ta�lara bakar e�er siyah ta� varsa ve ta��n arkas� bo�sa yeme hareketi olarak kaydeder
				for (m = 0; m < 7 - i; m++) {
					if (diziler[k][i] == "B" && (diziler[k][i + m] == "s" || diziler[k][i + m] == "S") && diziler[k][i + m + 1] == " ") {
						if ((diziler[k][i + m] == "s" || diziler[k][i + m] == "S") && (diziler[k][i + m - 1] == "s" || diziler[k][i + m - 1] == "S")) {
							continue;
						}
						yiyen[p] = to_string(i + m + 1);
						yiyen1[r] = to_string(k + 1);
						yenilen[s] = to_string(i + m);
						yenilen1[t] = to_string(k + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}
		for (i = 2; i < 8; i++) {									//beyaz dama i�in kontoller
			for (k = 0; k < 8; k++) {								//bu kontrol daman�n sol taraf�dndaki s�t�nlardaki ta�lara bakar e�er siyah ta� varsa ve ta��n arkas� bo�sa yeme hareketi olarak kaydeder
				for (m = 0; m < i; m++) {
					if (diziler[k][i] == "B" && (diziler[k][i - m] == "s" || diziler[k][i - m] == "S") && diziler[k][i - m - 1] == " ") {
						if ((diziler[k][i - m] == "s" || diziler[k][i - m] == "S") && (diziler[k][i - m + 1] == "s" || diziler[k][i - m + 1] == "S")) {
							continue;
						}
						yiyen[p] = to_string(i - m - 1);
						yiyen1[r] = to_string(k + 1);
						yenilen[s] = to_string(i - m);
						yenilen1[t] = to_string(k + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}

	}

	if (*tur == "s") {
		for (i = 0; i < 8; i++) {									//siyah ta�lar�n �st�ndeki ta�lar i�in yeme kontrolu
			for (k = 2; k < 7; k++) {								//ayn� �ekilde yaln�zca 7. sat�rdan 3. sat�ra kadar kontrol var
				if (diziler[k][i] == "s" && (diziler[k - 1][i] == "b" || diziler[k - 1][i] == "B") && diziler[k - 2][i] == " ") {
					yiyen[p] = to_string(i);
					yiyen1[r] = to_string(k - 1);
					yenilen[s] = to_string(i);
					yenilen1[t] = to_string(k);
					yiyen2[u] = to_string(i);
					yiyen3[v] = to_string(k + 1);
					p++;
					r++;
					s++;
					t++;
					u++;
					v++;
				}
			}
		}
		for (i = 0; i < 6; i++) {									//siyah ta�lar�n sa��ndaki ta�lar i�in yeme kontrolu
			for (k = 1; k < 7; k++) {								//ayn� �ekilde yaln�zca 1. s�tundan 6. s�tuna kadar kontrol var
				if (diziler[k][i] == "s" && (diziler[k][i + 1] == "b" || diziler[k][i + 1] == "B") && diziler[k][i + 2] == " ") {
					yiyen[p] = to_string(i + 2);
					yiyen1[r] = to_string(k + 1);
					yenilen[s] = to_string(i + 1);
					yenilen1[t] = to_string(k + 1);
					yiyen2[u] = to_string(i);
					yiyen3[v] = to_string(k + 1);
					p++;
					r++;
					s++;
					t++;
					u++;
					v++;
				}
			}
		}
		for (i = 2; i < 8; i++) {										//siyah ta�lar�n sa��ndaki ta�lar i�in yeme kontrolu		
			for (k = 1; k < 7; k++) {									//ayn� �ekilde yaln�zca 8. s�tundan 3. s�tuna kadar kontrol var
				if (diziler[k][i] == "s" && (diziler[k][i - 1] == "b" || diziler[k][i - 1] == "B") && diziler[k][i - 2] == " ") {
					yiyen[p] = to_string(i - 2);
					yiyen1[r] = to_string(k + 1);
					yenilen[s] = to_string(i - 1);
					yenilen1[t] = to_string(k + 1);
					yiyen2[u] = to_string(i);
					yiyen3[v] = to_string(k + 1);
					p++;
					r++;
					s++;
					t++;
					u++;
					v++;
				}
			}
		}
		for (i = 0; i < 8; i++) {
			for (k = 0; k < 6; k++) {						//Bu kontroller beyaz dama ta�lar�yla t�pa t�p ayn� fakat siyah damalar i�in 
				for (m = 0; m < 7 - k; m++) {
					if (diziler[k][i] == "S" && (diziler[k + m][i] == "b" || diziler[k + m][i] == "B") && diziler[k + m + 1][i] == " ") {
						if ((diziler[k + m][i] == "b" || diziler[k + m][i] == "B") && (diziler[k + m - 1][i] == "b" || diziler[k + m - 1][i] == "B")) {
							continue;
						}
						yiyen[p] = to_string(i);
						yiyen1[r] = to_string(k + m + 2);
						yenilen[s] = to_string(i);
						yenilen1[t] = to_string(k + m + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}
		for (i = 0; i < 8; i++) {
			for (k = 2; k < 8; k++) {								//Bu kontroller beyaz dama ta�lar�yla t�pa t�p ayn� fakat siyah damalar i�in
				for (m = 0; m < k; m++) {
					if (diziler[k][i] == "S" && (diziler[k - m][i] == "b" || diziler[k - m][i] == "B") && diziler[k - m - 1][i] == " ") {
						if ((diziler[k - m][i] == "b" || diziler[k - m][i] == "B") && (diziler[k - m + 1][i] == "b" || diziler[k - m + 1][i] == "B")) {
							continue;
						}
						yiyen[p] = to_string(i);
						yiyen1[r] = to_string(k - m);
						yenilen[s] = to_string(i);
						yenilen1[t] = to_string(k - m + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}
		for (i = 0; i < 6; i++) {
			for (k = 0; k < 8; k++) {								//Bu kontroller beyaz dama ta�lar�yla t�pa t�p ayn� fakat siyah damalar i�in
				for (m = 0; m < 7 - i; m++) {
					if (diziler[k][i] == "S" && (diziler[k][i + m] == "b" || diziler[k][i + m] == "B") && diziler[k][i + m + 1] == " ") {
						if ((diziler[k][i + m] == "b" || diziler[k][i + m] == "B") && (diziler[k][i + m - 1] == "b" || diziler[k][i + m - 1] == "B")) {
							continue;
						}
						yiyen[p] = to_string(i + m + 1);
						yiyen1[r] = to_string(k + 1);
						yenilen[s] = to_string(i + m);
						yenilen1[t] = to_string(k + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}
		for (i = 2; i < 8; i++) {
			for (k = 0; k < 8; k++) {											//Bu kontroller beyaz dama ta�lar�yla t�pa t�p ayn� fakat siyah damalar i�in
				for (m = 0; m < i; m++) {
					if (diziler[k][i] == "S" && (diziler[k][i - m] == "b" || diziler[k][i - m] == "B") && diziler[k][i - m - 1] == " ") {
						if ((diziler[k][i - m] == "b" || diziler[k][i - m] == "B") && (diziler[k][i - m + 1] == "b" || diziler[k][i - m + 1] == "B")) {
							continue;
						}
						yiyen[p] = to_string(i - m - 1);
						yiyen1[r] = to_string(k + 1);
						yenilen[s] = to_string(i - m);
						yenilen1[t] = to_string(k + 1);
						yiyen2[u] = to_string(i);
						yiyen3[v] = to_string(k + 1);
						p++;
						r++;
						s++;
						t++;
						u++;
						v++;
						break;
					}
				}
			}
		}
	}
	string gecici[50];
	for (i = 0; i < 50; i++) {		//ge�ici yi tamamen "" yap�yorum ki sorun ��kmas�n
		gecici[i] = "";
	}

	for (k = 0; k < 3; k++) {			//her dizi i�in farkl� farkl� d�ng� yazmamak i�in ge�iciye al�yorum
		if (k == 0) {
			for (p = 0; p < 50; p++) {
				gecici[p] = yiyen[p];
			}
		}
		if (k == 1) {
			for (p = 0; p < 50; p++) {
				gecici[p] = yiyen2[p];
			}
		}
		if (k == 2) {
			for (p = 0; p < 50; p++) {
				gecici[p] = yenilen[p];
			}
		}
		for (i = 0; i < 50; i++) {
			if (gecici[i] == "0") {			//s�t�nlar� harflere �eviriyorum ki kontrol a�amalar�nda komutu b�l�p kontrol edebileyim
				gecici[i] = "a";
			}
			if (gecici[i] == "1") {
				gecici[i] = "b";
			}
			if (gecici[i] == "2") {
				gecici[i] = "c";
			}
			if (gecici[i] == "3") {
				gecici[i] = "d";
			}
			if (gecici[i] == "4") {
				gecici[i] = "e";
			}
			if (gecici[i] == "5") {
				gecici[i] = "f";
			}
			if (gecici[i] == "6") {
				gecici[i] = "g";
			}
			if (gecici[i] == "7") {
				gecici[i] = "h";
			}
		}
		if (k == 0) {
			for (p = 0; p < 50; p++) {								//yeme hareketlerini ve yenilecek ta��n yerini dizilere at�yorum
				yiyen[p] = gecici[p];
			}
		}
		if (k == 1) {
			for (p = 0; p < 50; p++) {
				yiyen2[p] = gecici[p];
			}
		}
		if (k == 2) {
			for (p = 0; p < 50; p++) {
				yenilen[p] = gecici[p];
			}
		}
	}

	for (i = 0; i < 50; i++) {											//dizileri birle�tiriyorum ki bir dizide daha d�zenli tutabilmek i�in
		yenileny[i] = yenilen[i] + yenilen1[i];
	}
	for (i = 0; i < 50; i++) {
		yemehar[i] = yiyen2[i] + yiyen3[i] + yiyen[i] + yiyen1[i];
	}
	for (i = 0; i < 50; i++) {
		cout << yemehar[i];
	}
	for (i = 0; i < 50; i++) {
		cout << yenileny[i];
	}


	for (i = 0; i < 50; i++) {									//yeme hareketi yoksa 0 g�nderiyorum e�er yeme hareketi varsa 1 g�nderiyorum
		if (yemehar[i] != "") {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

void turdegis(FILE& dama) {
	string a;
	fopen("damaoyun.txt", "r+");
	fseek(&dama, 266, SEEK_SET);
	a = fgetc(&dama);
	if (a == "b") {													//bu fonksiyonu gerekti�inde kullan�yorum e�er yeme devam� varsa �a��rm�yorum
		fseek(&dama, 266, SEEK_SET);								//yada yanl�� hamle yap�ld�ysa
		fputs("s", &dama);											//tur kayd� s deyse b ye
	}																//b de ise s ye de�i�triyorum ki tur de�i�sin
	if (a == "s") {
		fseek(&dama, 266, SEEK_SET);
		fputs("b", &dama);
	}
	fclose(&dama);
}

bool turdevami(FILE& dama, string s1[8], string s2[8], string s3[8], string s4[8], string s5[8], string s6[8], string s7[8], string s8[8], string* tur, string yemehar[50], string yenileny[50], string* komut, string* k1, string* k2, FILE& turlar) {
	string k3, k4;
	char ar[5];
	string kom, har;
	kom = *komut;
	int i;
	bool devam = false;

	strcpy(ar, kom.c_str());							//komutu al�p char dizisinde iki par�aya b�l�yorum ta��n yeme hareketinden �nceki yeri ve yedikten sonra olaca�� yeri
	*k1 = ar[2];
	*k2 = ar[3];
	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 1) {				//e�er taramadan �nce yeme hareketi varsa turun devam� olmas� i�in yapt�m bu kontrol� yapmad���m zaman ayn� ta� yeme konumuna geldi�i an tur de�i�miyordu
		devam = true;
	}
	else if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 0) {
		devam = false;
	}

	tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);					//ard�ndan tarama yap�yorum ki e�er daha �nceki tur ta� yemi�se ve hala yeme hareketleri varsa alt tarafta ayn� ta� m� olup olmad���n� kontrol etmek ad�na


	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 1 && devam == true) {
		for (i = 0; i < 50; i++) {
			if (yemehar[i].substr(0, 1) == *k1 && yemehar[i].substr(1, 1) == *k2) {			//yeme hareketi yapm�� ta��n daha fazla yeme hareketi yap�p yapamayaca��n� kontrol ediyorum
				system("CLS");
				cout << "Ayni Tas ile Yemeye Devam\n";
				tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);
				yazdir(dama);
				komutal(tur, komut);														//devam etmesi i�in birdaha komut al�yorum
				kom = *komut;
				while (kom.substr(0, 1) != *k1 && kom.substr(1, 1) != *k2) {				//e�er verilen komut �nceki tur yeme hareketi yapm�� ta� i�in de�ilse veya o ta� yeme hareketi yapm�yorsa tekrar komut girilmesini istiyorum
					system("CLS");
					cout << "Hatali Hamle Ayni Tas ile Yemeye Devam\n";
					yazdir(dama);
					komutal(tur, komut);
					kom = *komut;
					tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);
				}
				if (kom.substr(0, 1) == *k1 && kom.substr(1, 1) == *k2) {					//e�er al�nan komut do�ruysa turu kaydediyorum
					if (pulhareketi(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, komut, yemehar, yenileny) == 1) {
						turlarikaydet(dama, turlar, komut);
						system("CLS");
					}
					tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);						//tarama yap�yorum ki e�er yenecek ta� kalmad�ysa bunu anlamak i�in
					if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 0) {
						turdegis(dama);														//e�er daha fazla yeme hareketi yoksa ayn� ta� i�in turu de�i�tiriyorum
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

void turlarikaydet(FILE& dama, FILE& turlar, string* komut) {
	char a;
	char ar[5];
	string kom;
	fopen("damaoyun.txt", "r");									//turun kime oldu�unu al�yorum ki : ile yazabileyim
	fseek(&dama, 266, SEEK_SET);
	a = fgetc(&dama);
	fclose(&dama);
	kom = *komut;												//komutu al�p char dizisine d�n��t�r�yorum dosyaya yazabilmek i�in

	strcpy(ar, kom.c_str());

	fopen("turlar.txt", "a");									//dosyan�n sonuna a komutu ile yaz�yorum
	fprintf(&turlar, "%c:%c%c%c%c\n\n", a, ar[0], ar[1], ar[2], ar[3]);
	fclose(&turlar);

}