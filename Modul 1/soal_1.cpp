#include<iostream>
using namespace std;
int main(){
	int beras,telur,minyak,totuang;
	cout<<"masukan harga beras : ";
	cin>>beras;
	cout<<"masukan harga telur : ";
	cin>>telur;
	cout<<"masukan harga minyak: ";
	cin>>minyak;
	cout<<"masukan total uang: ";
	cin>>totuang;
	//menjumlahkan total belanja
	int totalbelanja=(beras+telur+minyak);
	 //menghitung pajak
	 int pajak=(totalbelanja*0.25);
	 //menambah pajak ke total belanja
	 int Harga=totalbelanja+pajak;
	 //kembalian
	 int kembalian=totuang-Harga;
	 // Variabel untuk menyimpan jumlah lembar/koin
    int p100rb, p50rb, p20rb, p10rb, p5rb, p2rb, p1rb, p1koin, p500, p200, p100;
    
	// 5. Membagi kembalian ke dalam pecahan 
    int sisa = kembalian; 

    p100rb = sisa / 100000;
    sisa   = sisa % 100000;

    p50rb  = sisa / 50000;
    sisa   = sisa % 50000;

    p20rb  = sisa / 20000;
    sisa   = sisa % 20000;

    p10rb  = sisa / 10000;
    sisa   = sisa % 10000;

    p5rb   = sisa / 5000;
    sisa   = sisa % 5000;

    p2rb   = sisa / 2000;
    sisa   = sisa % 2000;

    p1rb   = sisa / 1000;
    sisa   = sisa % 1000;
    
    p1koin   = sisa / 1000;
    sisa   = sisa % 1000;

    p500   = sisa / 500;
    sisa   = sisa % 500;

    p200   = sisa / 200;
    sisa   = sisa % 200;

    p100   = sisa / 100;
    sisa   = sisa % 100;
	  
	  // Menampilkan struk sesuai format gambar
    cout << "\n============================================" << endl;
    cout << "|              STRUK KEMBALIAN             |" << endl;
    cout << "============================================" << endl;
    cout << "[Bina]: Nih, Than. Rincian kembaliannya:" << endl;
    cout << "Total Kembalian : Rp " << kembalian << endl;
    cout << "--------------------------------------------" << endl;
    cout << "- Rp 100.000 : " << p100rb << " lembar" << endl;
    cout << "- Rp 50.000  : " << p50rb  << " lembar" << endl;
    cout << "- Rp 20.000  : " << p20rb  << " lembar" << endl;
    cout << "- Rp 10.000  : " << p10rb  << " lembar" << endl;
    cout << "- Rp 5.000   : " << p5rb   << " lembar" << endl;
    cout << "- Rp 2.000   : " << p2rb   << " lembar" << endl;
    cout << "- Rp 1.000   : " << p1rb   << " lembar" << endl;
    cout << "- Rp 1.000   : " << p1rb   << " koin" << endl;
    cout << "- Rp 500     : " << p500   << " koin" << endl;
    cout << "- Rp 200     : " << p200   << " koin" << endl;
    cout << "- Rp 100     : " << p100   << " koin" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "[Fathan]: Aman! Sisa receh tak terpecahnya: Rp " << sisa << endl;
    cout << "Ini mau di Donasikan ga Ren?" << endl;
    cout << "[Rendy]: GAS" << endl;
    cout << "============================================" << endl;
    cout<<"harga+pajak"<<Harga<<endl;
	return 0;
}