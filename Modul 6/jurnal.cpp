#include<iostream>
using namespace std;

void menuUtama();
void View_Neural_Map();
void Inject_Neural_Thread();
void Purge_Corrupted_Link();
void Expand_Willpower();


int main (){
	while(true){
	int pilih;
	menuUtama();
	cin>>pilih;
	if(cin.fail()){
		cin.clear();
		cin.ignore(1000, '\n');
		cout<<"input salah !!"<<endl;
	}
	else if(pilih==1){
		View_Neural_Map();
	}
	else if(pilih==2){
		Inject_Neural_Thread();
	}
	else if(pilih==3){
		Purge_Corrupted_Link();
	}
	else if(pilih==4){
		Expand_Willpower();
	}
	else{
		break;
	}
}
return 0;	
}

void menuUtama(){
	
	cout<<"[1;35mXelisa: Exquisite... the synchronization is perfect.]"<<endl;
	cout<<"-----------------------------------------------------------"<<endl;
	cout<<"1. View Neural Map (Status)"<<endl;
	cout<<"2. Inject Neural Thread (Add)"<<endl;
	cout<<"3. Purge Corrupted Link (Delete)"<<endl;
	cout<<"4. Expand Willpower (Resize)"<<endl;
	cout<<"0. Surrender (Exit)"<<endl;
	cout<<"-----------------------------------------------------------"<<endl;
	cout<<"Select Operation: ";
	
	
	
}
void View_Neural_Map(){
	cout<<;
}

void Inject_Neural_Thread(){
	cout<<"hola";
}
void Purge_Corrupted_Link(){
	cout<<"hola";
}
void Expand_Willpower(){
	cout<<"hola";
}