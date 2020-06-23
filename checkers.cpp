#define _CRT_SECURE_NO_WARNINGS							//c foksiyonlarý kullanýrken hata vermemesi için yazdýðým bir satýr

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
	int sec = 0, i = 0;										//burada birçok tanýmlama yaptým ve pointer ile fonksiyonlara gönderdim ki
	string tur, k1, k2;										//ayný deðiþkenleri birçok fonksiyonda kullanabileyim diye
	FILE* dama;
	FILE* turlar;
	dama = fopen("damaoyun.txt", "a");						//eðer dosya yoksa oluþturmasý için
	fclose(dama);											//a ile açýyorum ki eðer dosya varsa silinmesin
	turlar = fopen("turlar.txt", "a");
	fclose(turlar);
	string s1[8], s2[8], s3[8], s4[8], s5[8], s6[8], s7[8], s8[8], yemehar[50], yenileny[50];		//kontroller için kullanýdýðým diziler
	string komut;																					//taþlarý dizilere alýyorum ki kontrol ederken
																									//daha verimli olsun
	while (sec != 3) {
		cout << "Komut Giriniz: \n";
		cout << "1)Yeni Oyun Olustur\n2)Devam Et\n3)Oyundan Cik(Herhangi Bir Zaman Kullanilabilir)\n";
		cin >> sec;
		system("CLS");
		switch (sec) {

		case 1:
			tabloyuolustur(*dama, *turlar);															//yeni oyun oluþturup seçim ekranýna döndürüyorum
			tarama(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur);
			system("CLS");
			cout << "Yeni Oyun Olusturuldu\n\n";
			break;
		case 2:
			while (sec != 3) {																		//devam et istenildðinde kullanýlabiliyor oyun yoksa önce oyun açýlmalý
				tarama(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur);								//her oyun baþý tarama ile taþlarý dizilere koyuyorum
				yazdir(*dama);
				yemekontrolu(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, yemehar, yenileny);		//yeme kotrollerini kontrol ediyorum
				if (komutal(&tur, &komut) == 0) {													//komut 0 döndürüyosa oyundan çýkýyorum
					sec = 3;
					break;
				}
				if ((pulhareketi(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, &komut, yemehar, yenileny)) == 0) {	//pul hareketi olmadýysa hata mesajý veriyorum
					system("CLS");
					cout << "Hatali Hamle\n";
				}
				else if ((pulhareketi(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, &komut, yemehar, yenileny)) == 1) {	//pul hareketi olduysa turlarý kayýt ediyorum
					turlarikaydet(*dama, *turlar, &komut);

					if ((turdevami(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur, yemehar, yenileny, &komut, &k1, &k2, *turlar)) == 1) {}
					else {
						system("CLS");																									// eðer tur devamý yoksa turu deðiþtiriyorum
						turdegis(*dama);
					}
				}
				donusum(*dama);																			//en son sona ulaþmýþ taþ varsa BB yada SS ye dönüþtürüyorum
				tarama(*dama, s1, s2, s3, s4, s5, s6, s7, s8, &tur);
			}
			break;
		case 3:																			//komut verme sýrasýnda çýkýþ yapýyor burda direkt seçim ekranýnda basýlýrsa diye yaptým
			break;
		default:
			cout << "Yanlis Tercih\n";
		}
	}
}
//açýklama satýrlarýný fonksiyonlarýn içine yerleþtirdim daha düzenli olmasý adýna	
void tabloyuolustur(FILE& dama, FILE& turlar) {
	fopen("damaoyun.txt", "w");															//dosyayý w ile açýyorum ki içindeki tüm bilgiler silinsin
	fprintf(&dama,																		//yeni oyun oluþtururken bu fonksiyon ile dosyaya direkt baþlangýç durumunu yazýyorum
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
	fclose(&turlar);																	// ayný þekilde turlarýda açýk kapýyorum w ile böylece yeni oyun oluþturulduðunda diðer oyunun verileri silinsin
	fopen("turlar.txt", "w");
	fclose(&turlar);
}

void yazdir(FILE& dama) {
	int a = 33, k, i;														//oyun konsol ekranýndan oynandýðý için dosyadaki veri bulunabilecek yerleri seçip hepsini diziye atýyorum
	int m = 0;															//sonrada ekrana yazdýrýyorum
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
	string c;												//bu fonksiyon sayesinde oyunda yeri deðiþen taþ olduðu an dizideki yerinide deðiþtiriyorum
	fopen("damaoyun.txt", "r+");							//böylece kontrolleri yaparken diziler üstünden kullanabileyim
	string* diziler[8] = { s1,s2,s3,s4,s5,s6,s7,s8 };		//ayný zamanda oyuna devam edildiði zaman taþlarý dizilere çekiyorum ki oyuna devam edilebilsin

	for (i = 0; i < 8; i++) {
		for (k = 0; k < 8; k++) {							//a1=33,a2=62,a3=91,a4=120,a5=149,a6=178,a7=207,a8=236;
			fseek(&dama, a, SEEK_SET);							//her bir taþ arasýnda 3 boþluk var bu yüzden 3 ekliyorum
			c = fgetc(&dama);									//her 8 sütünu okuduktan sonra aþaðýdaki ilk sütüna varabilmesi içinse 5 ekliyorum
			diziler[i][k] = c;
			a = a + 3;
		}
		a = a + s;
	}

	fseek(&dama, 266, SEEK_SET);							//burda da turun kimde olduðu bilgisini tutup diðer fonksiyonlarda kullanmak üzere
	c = fgetc(&dama);										//gönderiyorum
	*tur = c;

	fclose(&dama);
}

bool komutal(string* tur, string* komut) {
	string a;
	char ar[100];
	if (*tur == "b")
		cout << "Beyaz Hareket Gir:";						//eðer tur deðiþkeninde b varsa beyaz için komut istiyorum
	else {													//eðer tur deðiþkeninde s varsa siyah için komut istiyorum
		cout << "Siyah Hareket Gir:";
	}

	cin >> a;												//komutu alýyorum



	strcpy(ar, a.c_str());									//aldýðým stringi char dizisine atýyorum ki kontrol edebileyim

	if (a == "3") {											//komut verme sýrasýnda 3 e basýlýrsa oyundan çýkýlmasý için kontrol ediyorum
		return 0;
	}

	for (; a.length() != 4;) {								//string uzunluðu 4 ten büyükse hatalý hamle olduðunu ekrana yazdýrýp birdaha alýyorum
		cout << "Hatali Hamle Tekrar Giriniz\n";			//bunu try içinde yapmamýn sebebi bazý girdiler sonucu programýn kapanmasý
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
					string komutt(ar);										//eðer char dizisi istenen formattaysa komut alýnýyor ve stringe geri dönüþtürülüyor
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

	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 1) {			//Bu if kontrolule hareket sýrasýnda yeme zorunluluðu varsa
		for (i = 0; i < 50; i++) {																	//yeme hamlesi yapýlmasý için zorluyorum
			if (*komut == yemehar[i]) {																//bu deðiþkenleri daha aþaðýdaki bir fonksiyondan alýyorum								
				hareket = yemehar[i];																//eðer komut yeme yapýlmasý için gereken hareketle aymý ise deðiþkene ata
				yok = yenileny[i];																	//yenilecek taþýn pozisyonunu deðiþkene ata
				break;
			}
		}
		if (hareket != *komut) {
			system("CLS");																			//eðer komut herhangi bir yeme hareketiyle eþit deðilse yeme zorunluluðu olduðu için
			cout << "Hatali Hamle Yemen Gerekiyor\n";												//hata ver
			return 0;
		}
		strcpy(ar2, hareket.c_str());																//aldýðýmýz deðiþkenleri char dizilerine atýyorum ki kontrol edebilmek için
		strcpy(ar3, yok.c_str());

		if (*tur == "b") {																			//tur beyazýnsa
			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "b") {								//seçilen taþ b ise
				fopen("damaoyun.txt", "r+");
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);			//yediði taþý al
				l = fgetc(&dama);
				fseek(&dama, 33 + (29 * (ar2[3] - '0' - 1)) + 3 * (ar2[2] % 97), SEEK_SET);			//gideceði yere b yaz
				fputs("b", &dama);
				fseek(&dama, 33 + (29 * (ar2[1] - '0' - 1)) + 3 * (ar2[0] % 97), SEEK_SET);			//daha önce olduðu yeri ve yediði taþ yerine " " yaz
				fputs(" ", &dama);
				fseek(&dama, 33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97), SEEK_SET);
				fputs(" ", &dama);
				if (l == 'S') {
					fseek(&dama, (33 + (29 * (ar3[1] - '0' - 1)) + 3 * (ar3[0] % 97)) - 1, SEEK_SET);	//eðer yenen taþ S ise bir önceki noktayýda sil çünkü damalar SS diye dosyaya yazýlý
					fputs(" ", &dama);
				}
				fclose(&dama);
				return 1;
			}

			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "B") {					//ayný durumlar ayný þekilde diðer yeme hareketleri içinde geçeli
				fopen("damaoyun.txt", "r+");											//beyaz dama yani B için
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
			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "s") {					//s taþlar için
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
			if (diziler[ar2[1] - '0' - 1][int(ar2[0]) % 97] == "S") {					//siyah dama yani S için
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


	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 0) {								//bu kýsým yeme zorunluluðu olmayan hareketlerde geçerli
		if (*tur == "b") {
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "b") {														//seçilen taþ b ise ve pul hareketi aþaðý doðruysa
				if ((abs(ar[0] - ar[2]) == 1 && abs(ar[1] - ar[3]) == 0)) {
					fopen("damaoyun.txt", "r+");
					if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == " ") { return 0; }									//seçilen yer boþsa çýk
					if (diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "b" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "s" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "B" || diziler[ar[3] - '0' - 1][int(ar[2]) % 97] == "S") { return 0; }	//gidilecek yerde taþ varsa çýk
					fseek(&dama, 33 + (29 * (ar[3] - '0' - 1)) + 3 * (ar[2] % 97), SEEK_SET);		//bu if komutlarýný geçerse
					fputs("b", &dama);																//gidilecek yere taþý koy
					fseek(&dama, 33 + (29 * (ar[1] - '0' - 1)) + 3 * (ar[0] % 97), SEEK_SET);
					fputs(" ", &dama);																//önceki olduðu yerden taþý sil
					fclose(&dama);
					return 1;
				}
			}
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "b") {			//seçilen taþ b ise ve hareket saða yada sola doðruysa
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
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "B") {								//seçilen taþ B ise ve hareket aþaðý yada yukarý doðruysa
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
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "B") {										//seçilen taþ B ise ve hareket saða yada sola doðruysa		
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
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "s") {						//seçilen taþ s ise ve hareket yukarý doðruysa
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
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "s") {							//seçilen taþ s ise ve hareket saða yada sola doðruysa
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
			if (diziler[ar[3] - '0' - 1][int(ar[0]) % 97] == "S") {														//seçilen taþ S ise ve hareket yukarý yada aþaðý doðruysa
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
			if (diziler[ar[1] - '0' - 1][int(ar[0]) % 97] == "S") {											//seçilen taþ S ise ve hareket saða yada sola doðruysa
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
	cout << "Hatali Hamle\n";						//komut hiç bir harekete uymuyorsa yada hatalý bir komut girildiysa hata mesajý
	return 0;
}

void donusum(FILE& dama) {
	int i = 0;
	char a;
	fopen("damaoyun.txt", "r+");
	for (i = 0; i < 8; i++) {										//tüm 8. sütunu tarýyorum eðer beyaz taþ varsa damaya çeviriyorum
		fseek(&dama, 236 + 3 * i, SEEK_SET);						//238 8. sütunun baþlangýcý
		a = fgetc(&dama);
		if (a == 'b') {
			fseek(&dama, 236 + 3 * i, SEEK_SET);
			fputs("B", &dama);
			fseek(&dama, (236 + 3 * i) - 1, SEEK_SET);
			fputs("B", &dama);
		}
	}
	for (i = 0; i < 8; i++) {										//tüm 1. sütunu tarýyorum eðer siyah taþ varsa damaya çeviriyorum
		fseek(&dama, 33 + 3 * i, SEEK_SET);							//33 1. sütunun baþlangýç karesini yeri ve 3 ün katlarýyla toplama sebebim
		a = fgetc(&dama);											// yanýndaki sütün ondan 3 birim uzakta
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

	if (*tur == "b") {									//tur beyazýnsa
		for (i = 0; i < 8; i++) {
			for (k = 1; k < 6; k++) {					//beyaz taþýn aþaðýsýnda yenebilecek taþ var mý diye kontrol ediyorum 2. satýdan 6. satýra kadar kontrol var çünkü beyaz bir taþ 7. satýrdaysa ve 8. satýrda bir siyah taþ varsa bunu yiyemez ve biçbir normal beyaz taþ 1. satýrda bulunamaz bu mantýkla diðer taþlar içinde kontorl yaptým
				if (diziler[k][i] == "b" && (diziler[k + 1][i] == "s" || diziler[k + 1][i] == "S") && diziler[k + 2][i] == " ") {		//eðer komuttaki taþ b ise ve önünde S yada s varsa ve onlarýn altýndaki satýr boþsa devam et
					yiyen[p] = to_string(i);
					yiyen1[r] = to_string(k + 3);				//k larý hep 1 le toplamamýn sebebi 1. satýrýn 0. dizi olmasý
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
		for (i = 0; i < 6; i++) {								//beyaz taþlarýn saðýndaki taþlar için yeme kontrolu
			for (k = 1; k < 7; k++) {							//ayný þekilde yalnýzca 1. sütundan 6. sütuna kadar kontrol var
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
		for (i = 2; i < 8; i++) {								//beyaz taþlarýn solundaki taþlar için yeme kontrolu
			for (k = 1; k < 7; k++) {							//ayný þekilde yalnýzca 8. sütundan 3. sütuna kadar kontrol var
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
		for (i = 0; i < 8; i++) {								//beyaz dama için kontoller
			for (k = 0; k < 6; k++) {							//bu kontrol damanýn altýndaki satýrdaki taþlara bakar eðer siyah taþ varsa ve taþýn arkasý boþsa yeme hareketi olarak kaydeder
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
		for (i = 0; i < 8; i++) {								//beyaz dama için kontoller
			for (k = 2; k < 8; k++) {							//bu kontrol damanýn üstündeki satýrlardaki taþlara bakar eðer siyah taþ varsa ve taþýn arkasý boþsa yeme hareketi olarak kaydeder
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
		for (i = 0; i < 6; i++) {								//beyaz dama için kontoller
			for (k = 0; k < 8; k++) {							//bu kontrol damanýn sað tarafýdndaki sütünlardaki taþlara bakar eðer siyah taþ varsa ve taþýn arkasý boþsa yeme hareketi olarak kaydeder
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
		for (i = 2; i < 8; i++) {									//beyaz dama için kontoller
			for (k = 0; k < 8; k++) {								//bu kontrol damanýn sol tarafýdndaki sütünlardaki taþlara bakar eðer siyah taþ varsa ve taþýn arkasý boþsa yeme hareketi olarak kaydeder
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
		for (i = 0; i < 8; i++) {									//siyah taþlarýn üstündeki taþlar için yeme kontrolu
			for (k = 2; k < 7; k++) {								//ayný þekilde yalnýzca 7. satýrdan 3. satýra kadar kontrol var
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
		for (i = 0; i < 6; i++) {									//siyah taþlarýn saðýndaki taþlar için yeme kontrolu
			for (k = 1; k < 7; k++) {								//ayný þekilde yalnýzca 1. sütundan 6. sütuna kadar kontrol var
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
		for (i = 2; i < 8; i++) {										//siyah taþlarýn saðýndaki taþlar için yeme kontrolu		
			for (k = 1; k < 7; k++) {									//ayný þekilde yalnýzca 8. sütundan 3. sütuna kadar kontrol var
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
			for (k = 0; k < 6; k++) {						//Bu kontroller beyaz dama taþlarýyla týpa týp ayný fakat siyah damalar için 
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
			for (k = 2; k < 8; k++) {								//Bu kontroller beyaz dama taþlarýyla týpa týp ayný fakat siyah damalar için
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
			for (k = 0; k < 8; k++) {								//Bu kontroller beyaz dama taþlarýyla týpa týp ayný fakat siyah damalar için
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
			for (k = 0; k < 8; k++) {											//Bu kontroller beyaz dama taþlarýyla týpa týp ayný fakat siyah damalar için
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
	for (i = 0; i < 50; i++) {		//geçici yi tamamen "" yapýyorum ki sorun çýkmasýn
		gecici[i] = "";
	}

	for (k = 0; k < 3; k++) {			//her dizi için farklý farklý döngü yazmamak için geçiciye alýyorum
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
			if (gecici[i] == "0") {			//sütünlarý harflere çeviriyorum ki kontrol aþamalarýnda komutu bölüp kontrol edebileyim
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
			for (p = 0; p < 50; p++) {								//yeme hareketlerini ve yenilecek taþýn yerini dizilere atýyorum
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

	for (i = 0; i < 50; i++) {											//dizileri birleþtiriyorum ki bir dizide daha düzenli tutabilmek için
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


	for (i = 0; i < 50; i++) {									//yeme hareketi yoksa 0 gönderiyorum eðer yeme hareketi varsa 1 gönderiyorum
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
	if (a == "b") {													//bu fonksiyonu gerektiðinde kullanýyorum eðer yeme devamý varsa çaðýrmýyorum
		fseek(&dama, 266, SEEK_SET);								//yada yanlýþ hamle yapýldýysa
		fputs("s", &dama);											//tur kaydý s deyse b ye
	}																//b de ise s ye deðiþtriyorum ki tur deðiþsin
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

	strcpy(ar, kom.c_str());							//komutu alýp char dizisinde iki parçaya bölüyorum taþýn yeme hareketinden önceki yeri ve yedikten sonra olacaðý yeri
	*k1 = ar[2];
	*k2 = ar[3];
	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 1) {				//eðer taramadan önce yeme hareketi varsa turun devamý olmasý için yaptým bu kontrolü yapmadýðým zaman ayný taþ yeme konumuna geldiði an tur deðiþmiyordu
		devam = true;
	}
	else if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 0) {
		devam = false;
	}

	tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);					//ardýndan tarama yapýyorum ki eðer daha önceki tur taþ yemiþse ve hala yeme hareketleri varsa alt tarafta ayný taþ mý olup olmadýðýný kontrol etmek adýna


	if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 1 && devam == true) {
		for (i = 0; i < 50; i++) {
			if (yemehar[i].substr(0, 1) == *k1 && yemehar[i].substr(1, 1) == *k2) {			//yeme hareketi yapmýþ taþýn daha fazla yeme hareketi yapýp yapamayacaðýný kontrol ediyorum
				system("CLS");
				cout << "Ayni Tas ile Yemeye Devam\n";
				tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);
				yazdir(dama);
				komutal(tur, komut);														//devam etmesi için birdaha komut alýyorum
				kom = *komut;
				while (kom.substr(0, 1) != *k1 && kom.substr(1, 1) != *k2) {				//eðer verilen komut önceki tur yeme hareketi yapmýþ taþ için deðilse veya o taþ yeme hareketi yapmýyorsa tekrar komut girilmesini istiyorum
					system("CLS");
					cout << "Hatali Hamle Ayni Tas ile Yemeye Devam\n";
					yazdir(dama);
					komutal(tur, komut);
					kom = *komut;
					tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);
				}
				if (kom.substr(0, 1) == *k1 && kom.substr(1, 1) == *k2) {					//eðer alýnan komut doðruysa turu kaydediyorum
					if (pulhareketi(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, komut, yemehar, yenileny) == 1) {
						turlarikaydet(dama, turlar, komut);
						system("CLS");
					}
					tarama(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur);						//tarama yapýyorum ki eðer yenecek taþ kalmadýysa bunu anlamak için
					if (yemekontrolu(dama, s1, s2, s3, s4, s5, s6, s7, s8, tur, yemehar, yenileny) == 0) {
						turdegis(dama);														//eðer daha fazla yeme hareketi yoksa ayný taþ için turu deðiþtiriyorum
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
	fopen("damaoyun.txt", "r");									//turun kime olduðunu alýyorum ki : ile yazabileyim
	fseek(&dama, 266, SEEK_SET);
	a = fgetc(&dama);
	fclose(&dama);
	kom = *komut;												//komutu alýp char dizisine dönüþtürüyorum dosyaya yazabilmek için

	strcpy(ar, kom.c_str());

	fopen("turlar.txt", "a");									//dosyanýn sonuna a komutu ile yazýyorum
	fprintf(&turlar, "%c:%c%c%c%c\n\n", a, ar[0], ar[1], ar[2], ar[3]);
	fclose(&turlar);

}