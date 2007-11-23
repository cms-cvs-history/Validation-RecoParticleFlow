{
// initialize the core of the framework, and load the PFRootEvent 
// library, which contains the ROOT interface

gSystem->Load("libFWCoreFWLite.so");
gSystem->Load("libRecoParticleFlowBenchmark.so");
AutoLibraryLoader::enable();
gSystem->Load("libCintex.so");

//ROOT::Cintex::Cintex::Enable();

// create a PFRootEventManager
PFBenchmarkAlgo my_obj;


// look for ECAL rechit with maximum energy

}
