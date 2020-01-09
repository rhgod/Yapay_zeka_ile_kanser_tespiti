#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {
	FILE* fp;
	int arrEgitim[600][10], arrTest[83][10], komut;
	int sayi1, sayi2, sayi3, sayi4, sayi5, sayi6, sayi7, sayi8, sayi9, sayi10;

	fopen_s(&fp, "egitim.txt", "r");

	for (int i = 0; i < 600; i++) // Döngü txt dosyasindaki tüm satirlari teker teker areEgtim'e atiyor.
	{
		fscanf_s(fp, "%*d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &sayi1, &sayi2, &sayi3, &sayi4, &sayi5, &sayi6, &sayi7, &sayi8, &sayi9, &sayi10);
		arrEgitim[i][0] = sayi1;
		arrEgitim[i][1] = sayi2;
		arrEgitim[i][2] = sayi3;
		arrEgitim[i][3] = sayi4;
		arrEgitim[i][4] = sayi5;
		arrEgitim[i][5] = sayi6;
		arrEgitim[i][6] = sayi7;
		arrEgitim[i][7] = sayi8;
		arrEgitim[i][8] = sayi9;
		arrEgitim[i][9] = sayi10;
	}
	fclose(fp);

	fopen_s(&fp, "test.txt", "r");

	for (int i = 0; i < 83; i++) // Döngü txt dosyasindaki tüm satirlari teker teker arrTest'e atiyor.
	{
		fscanf_s(fp, "%*d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &sayi1, &sayi2, &sayi3, &sayi4, &sayi5, &sayi6, &sayi7, &sayi8, &sayi9, &sayi10);
		arrTest[i][0] = sayi1;
		arrTest[i][1] = sayi2;
		arrTest[i][2] = sayi3;
		arrTest[i][3] = sayi4;
		arrTest[i][4] = sayi5;
		arrTest[i][5] = sayi6;
		arrTest[i][6] = sayi7;
		arrTest[i][7] = sayi8;
		arrTest[i][8] = sayi9;
		arrTest[i][9] = sayi10;
	}
	fclose(fp);
	//                     Menu kismi                          //
	printf("Merhabalar kNN algoritmasi ile kanser tespiti programina hosgeldiniz.\n");
kontrol1:
	printf("\nTest dosyasini hesaplamak icin => 1 giriniz.\nKullanicidan parametre alip hesaplamak icin => 2 giriniz.\nProgrami sonlandirmak icin => 0 giriniz.\nGiris: ");
	scanf_s("%d", &komut);
	if (komut == 1) {
		TestSonucBulma(arrEgitim, arrTest);
		printf("\nTekrar islem yapmak istiyorsaniz => 1 giriniz.\nProgrami sonlandirmak icin => 0 giriniz.\nGiris: ");
	kontrol3:
		scanf_s("%d", &komut);
		if (komut == 1) goto kontrol1;
		else if (komut == 0) goto kontrol2;
		else {
			printf("HATALI KOMUT TEKRAR GIRIN\n ");
			goto kontrol3;
		}
	}
	else if (komut == 2) {
		KullaniciGirisiHesaplama(arrEgitim);
		printf("\nTekrar islem yapmak istiyorsaniz => 1 giriniz.\nProgrami sonlandirmak icin => 0 giriniz.\nGiris: ");
	kontrol4:
		scanf_s("%d", &komut);
		if (komut == 1) goto kontrol1;
		else if (komut == 0) goto kontrol2;
		else {
			printf("HATALI KOMUT TEKRAR GIRIN\n ");
			goto kontrol4;
		}
	}
	else if (komut == 0) goto kontrol2;
	else {
		printf("HATALI KOMUT TEKRAR GIRIN");
		goto kontrol1;
	}

kontrol2:
	printf("\n\nYine bekleriz gorusmek uzere...\n\n");
	return 0;
}

int TestSonucBulma(int arrEgitim[600][10], int arrTest[83][10]) { // Test verilerindeki sonucu bulan fonksiyon. // 
	int a, i, j, z, Testsonuc, HastalikDegeri, min_idx, TempVal, TempVal2, hasta = 0, hastadegil = 0, arrTestSonuc[600][2], arrTestSonucDY[6];
	int k = 5; // en yakin k komsu >>>> bu degeri degistirirken arrTestSonucDY[k+1][1] da degismeli
	float  dogruSayisi = 0, yanlisSayisi = 0;
	char arrTestSonucDYCHAR[83];

	for (a = 0; a < 83; a++)
	{
		for (j = 0; j < 600; j++)
		{
			Testsonuc = 0;

			for (z = 0; z < 9; z++) // Bu dongu Uzakliklari bulup arrTestSonucun 0. indeksine uzakligi 1. indeksine 2 veya 4 olarak hastalik degerini atiyor.
			{

				int arrEgitimtemp = arrEgitim[j][z];
				int arrTesttemp = arrTest[a][z];

				Testsonuc = Testsonuc + pow((arrEgitimtemp - arrTesttemp), 2);

			}
			arrTestSonuc[j][0] = Testsonuc;
			HastalikDegeri = arrEgitim[j][9];
			arrTestSonuc[j][1] = HastalikDegeri;
		} 
		
		//SELECTION SORT Siralama >> 2 boyutlu diziyi siralama icin yanlarina [0] ekledim. Bu sayede arrtestSonuc[600][0] a bagli olarak siraliyor ve elimizde sirali 600 deger oluyor.
		for (i = 0; i < 599; i++)
		{
			min_idx = i;
			for (j = i + 1; j < 600; j++)
				if (arrTestSonuc[j][0] < arrTestSonuc[min_idx][0])
					min_idx = j;
			//Uzaklik
			TempVal = arrTestSonuc[min_idx][0];
			arrTestSonuc[min_idx][0] = arrTestSonuc[i][0];
			arrTestSonuc[i][0] = TempVal;
			//Hastalik degeri
			TempVal = arrTestSonuc[min_idx][1];
			arrTestSonuc[min_idx][1] = arrTestSonuc[i][1];
			arrTestSonuc[i][1] = TempVal;
		}

		printf("~~~~~~~~~~~~~~~~~~ %d. Test verisi ~~~~~~~~~~~~~~~~~~\n\n", a + 1);
		for (i = 0; i < k; i++) {

			printf("%d. Deger icin Uzaklik degeri: %d, Hastalik degeri: %d\n", i+1,arrTestSonuc[i][0], arrTestSonuc[i][1]);
		}

		hasta = 0;
		hastadegil = 0;
		for (i = 0; i < k; i++) // En yakin k komsu eger 2 ise hastadegil 4 ise hasta degerini arttiriyor >>
		{
			TempVal2 = arrTestSonuc[i][1];
			if (TempVal2 == 2) hastadegil++;
			else hasta++;

		}

		printf("\n%d. Test Verisi Sonuclari: Hasta: %d, Hasta degil: %d\n\n", a + 1, hasta, hastadegil);
		for (i = 0; i < k; i++) // En yakin k komsu eger 2 ise hastadegil 4 ise hasta degerini arttiriyor >>
		{
			if (hastadegil > hasta) arrTestSonucDY[i] = 2; // Eger hastadegil degeri hasta degerden fazla ise arrTestSonucDY dizisine 2 atiyor.
			else arrTestSonucDY[i] = 4; // Hasta degeri fazla ise 4 atiyor.

			if (arrTestSonucDY[i] == arrTest[a][9]) arrTestSonucDYCHAR[a] = 'D'; // Deger test verisindeki deger ile ayni ise D
			else arrTestSonucDYCHAR[a] = 'Y'; // Farkli ise Y yaziyor.
		}
		
	}

	for (int g = 0; g < 83; g++) //sonuclari ekrana yazdiriyor.
	{  
		printf("%d. veri == %c\n", g + 1, arrTestSonucDYCHAR[g]);
		if (arrTestSonucDYCHAR[g] == 'D') dogruSayisi++;
		else yanlisSayisi++;
	}

	printf("\nDogru sayisi: %.0f\nYanlis sayisi: %.0f\n", dogruSayisi, yanlisSayisi);
	printf("Basari orani yuzde: %.2f\n", ((dogruSayisi * 100) / 83));
}

int KullaniciGirisiHesaplama(int arrEgitim[600][10]) {
	int arrKullaniciGirisi[9], arrKullaniciUzaklik[600][2], TempVal, TempVal2, Testsonuc, HastalikDegeri, i, j, min_idx;
	int k = 15, hasta = 0, hastadegil = 0;

	for (i = 0; i < 9; i++)
	{
		printf("%d. degeri giriniz: ", i + 1);
		scanf_s("%d", &TempVal);
		arrKullaniciGirisi[i] = TempVal;
	}

	for (j = 0; j < 600; j++)
	{
		Testsonuc = 0;
		for (int z = 0; z < 9; z++) // Uzakliklari bulup arrTestSonucun 0. indeksine uzakligi 1. indeksine 2 veya 4 olarak hastalik degerini atiyor.
		{
			Testsonuc = Testsonuc + pow((arrEgitim[j][z] - arrKullaniciGirisi[z]), 2);
			HastalikDegeri = arrEgitim[j][9];

			arrKullaniciUzaklik[j][0] = Testsonuc;
			arrKullaniciUzaklik[j][1] = HastalikDegeri;
		}
	}

	for (i = 0; i < 599; i++) // Siralama 
	{

		min_idx = i;
		for (j = i + 1; j < 600; j++)
			if (arrKullaniciUzaklik[j][0] < arrKullaniciUzaklik[min_idx][0])
				min_idx = j;

		TempVal = arrKullaniciUzaklik[min_idx][0];
		arrKullaniciUzaklik[min_idx][0] = arrKullaniciUzaklik[i][0];
		arrKullaniciUzaklik[i][0] = TempVal;

		TempVal = arrKullaniciUzaklik[min_idx][1];
		arrKullaniciUzaklik[min_idx][1] = arrKullaniciUzaklik[i][1];
		arrKullaniciUzaklik[i][1] = TempVal;
	}

	for (i = 0; i < k; i++) // En yakin k komsu eger 2 ise hastadegil 4 ise hasta degerini arttiriyor. 
	{
		TempVal2 = arrKullaniciUzaklik[i][1];
		if (TempVal2 == 2) hastadegil++;
		else hasta++;
	}

	if (hastadegil > hasta) printf("\nHasta degilsiniz. :D");
	else printf("\nKansersiniz. :(");
}