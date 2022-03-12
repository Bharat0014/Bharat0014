#include<iostream>

#include "Pythia8/Pythia.h"

#include "TFile.h"
#include "TTree.h"
using namespace Pythia8;
int main()
{

TFile *output = new TFile("drell_yan.root", "recreate");
TTree *tree = new TTree("tree", "tree");

int id,event,size,no;
double m,px,py,pz,pt,energy;
double pabs,dndys,mo1,mo2,doo1,doo2,spi,moo;
string idmo1,idmo2,iddoo1,iddoo2;
string namee;
tree->Branch("event", &event,"event/I");
tree->Branch("size", &size,"size/I");
tree->Branch("no", &no,"no/I");
tree->Branch("id", &id,"id/I");
tree->Branch("px", &px,"px/D");
tree->Branch("py", &py,"py/D");
tree->Branch("pz", &pz,"pz/D");
tree->Branch("m", &m,"m/D");
tree->Branch("energy", &energy,"energy/D");
tree->Branch("pt", &pt,"pt/D");
tree->Branch("pabs", &pabs,"pabs/D");
tree->Branch("dndys", &dndys,"dndys/D");
//tree->Branch("mo2", &mo2,"mo2/D");
int nevents = 1e5;



Pythia pythia;
//Event& event = pythia.event;
pythia.readString("Beams:idA = 2212");
pythia.readString("Beams:idB = 2212");
pythia.readString("Beams:eCM = 7e3");
pythia.readString("Beams:frameType = 1");
//pythia.readString("WeakBosonExchange:all = on");
//pythia.readString("WeakSingleBoson:all = on");

//pythia.readString("WeakDoubleBoson:all = on");

pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
pythia.readString("Processlevel:all = on");
pythia.readString("ProcessLevel:resonanceDecays = on");
pythia.readString("PartonLevel:MPI = off");
pythia.readString("HadronLevel:all = off");




//pythia.readString("PartonLevel:ISR = off");
//pythia.readString("PartonLevel:FSR = off");
//pythia.readString("HadronLevel:decay = on");
//pythia.readString("SUSY:all = on");
//pythia.readString(" SUSY:qqbar2sleptonantislepton = on");
//pythia.readString("WeakBosonAndParton:all = on");
//pythia.readString("PhotonCollision:all = on");
//pythia.readString("PromptPhoton:all = on");   
//pythia.readString("SoftQCD:all = on");
//pythia.readString("HardQCD:all = on");

  
  
 
 
        
pythia.init();

Hist pTnoEnh("PT spectrum", 30, 0., 10.);
//Hist pTwithEnh("PT spectrum with  Enhancement", 100, 0., 500.);
//Hist nFinal("final particle multiplicity", 100, -0.5, 1599.5);
//Hist nCharged("charged particle multiplicity", 100, -0.5, 799.5);
Hist dndy("dn/dy for charged particles", 100, -10., 10.);
Hist dndeta("p for charged particles", 100, 0, 10.);
Hist dndpT("e for charged particles", 100, 0., 10.);
//Hist epCons("deviation from energy-momentum conservation", 100, 0., 1e-6);

for(int i =0; i<nevents; i++){
if(!pythia.next()) continue;
int entries = pythia.event.size();
//std::cout<<"Event: "<<i<<std::endl;
//std::cout<<"Event Size: "<<entries<<std::endl;

event =i;
size = entries;
int iZ = 0;
for(int j =0;j<entries;j++){

 if(pythia.event[j].id() == 23 )
{
id = pythia.event[j].id();
m = pythia.event[j].m();
namee = pythia.event[j].name();
mo1 = pythia.event[j].mother1();
//idmo1 = pythia.event[mo1].name();
mo2 = pythia.event[j].mother2();
//idmo2 = pythia.event[mo2].name();
doo1 = pythia.event[j].daughter1();
iddoo1 = pythia.event[doo1].name();
doo2 = pythia.event[j].daughter2();
iddoo2 = pythia.event[doo2].name();
//moo = pythia.event[j].mother();

cout<< namee<<"    Mother 1, Mother 2 = "<<pythia.event[mo1].name()<<" , "<<pythia.event[mo2].name()<<endl;
no = j;
spi= pythia.event[j].spinType();
 px = pythia.event[j].px();
 py = pythia.event[j].py();
 pz = pythia.event[j].pz();
  dndys = pythia.event[j].y();
energy = pythia.event[j].e();
 //namee = pythia.event[j].name();


dndpT.fill( energy);
   pt = pythia.event[j].pT();
    pabs = sqrt(pow(px,2)+pow(py,2)+pow(pz,2));
dndy.fill( pythia.event[j].y() );
dndeta.fill(pabs);
dndpT.fill(pt);
//pTnoEnh.fill(pt);
tree->Fill();
//cout<<idmo1<<"   "<<idmo2<<"   "<<"   "<<iddoo1<<"  "<<iddoo2<<endl;

}

}
}

//pythia.event.list(gamma);
pythia.stat();
  
output->Write();
output->Close();
//cout<<mo<<endl;
cout<<dndy<<dndpT<<dndeta;
return 0;
}

