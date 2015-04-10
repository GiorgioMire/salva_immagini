/* Assegnato da Giacomo il 1/4/2015

/* 	Esercizio #1 */
/*  Fase Preliminare pratica di Opencv */

/* 	Lo scopo di questo codice è salvare alcune immagini
   	che verranno usate da un altro tool 
	per effettuare la calibrazione di una singola camera*/


/* Inclusione librerie di opencv*/
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include "opencv2/core/core.hpp"
 #include <opencv2/calib3d/calib3d.hpp>

 /* Inclusione di iostream*/
 #include <iostream>

/* namespace utilizzati*/
using namespace cv;
using namespace std;

/* Dichiarazione funzioni*/
/* Funzione che scrive sullo stream di uscita un testo*/
void scrivi(string messaggio);


/* Funzione main*/
int main(){

/*apro una finestra*/
namedWindow("Acquisizione da webcam",WINDOW_AUTOSIZE);
	

/*Dichiarazione di variabili*/
int contatore=0;		 /*Conta il numero di immagini salvate*/
bool trovato;			/* Indica quando viene trovato il pattern nell'immagine*/
std::vector<Point2f> corners; /* Vettore di punti 2D dei corner della scacchiera nell'immagine*/
Size boardSize(9,6); /* Numero di corner in verticale e in orizzontale nella scacchiera*/
/*___________________*/
	
 
    //scrivi("Inizializzo la cattura");


	VideoCapture cap;
/* Apro lo stream della webcam principale*/
	cap.open(0);

/* Errore se non riesco ad aprire lo stream della camera principale */
	if(!cap.isOpened()){
		cout<<endl<<"Non sono riuscito ad accedere alla camera"<<endl;
		return -1;
	}


	
	
	//scrivi("Inizio cliclo");
	while(1){
	Mat frame; /* Immagine visualizzata (su cui disegno anche i corner della scacchiera)*/
	Mat frame_pulito; /* Immagine eventualmente salvata (senza corner disegnati)*/

	//scrivi("Acquisisco il frame");
	cap.read(frame);
	frame_pulito=frame.clone();
		

	
	/* Cerco la scacchiera nell'immagine*/
	bool trovata_scacchiera= findChessboardCorners(frame, boardSize, corners,

        CALIB_CB_ADAPTIVE_THRESH 
        //Use adaptive thresholding to convert the image to black and white,
		// rather than a fixed threshold level (computed from the average image brightness)
         + CALIB_CB_NORMALIZE_IMAGE
         //Normalize the image gamma with equalizeHist() before applying fixed or adaptive thresholding.
        + CALIB_CB_FAST_CHECK
        //Run a fast check on the image that looks for chessboard corners, and shortcut the call if none is found.
        //This can drastically speed up the call in the degenerate condition when no chessboard is observed.);

	/*Disegno i corner della scacchiera*/
	drawChessboardCorners(frame, boardSize, Mat(corners), trovata_scacchiera);
	imshow("Acquisizione da webcam",frame);
	char key=waitKey(100);
	if(key==27){
				scrivi("operazione terminata dall'utente");
				break;
				}

	if (trovata_scacchiera){
							scrivi("Scacchiera trovata");
							scrivi("Salvare immagine? y/n");

							while(1){
							char key=waitKey(1000);

								if (key==int('y')) {
								
													trovata_scacchiera==false;
													contatore++;

													/* conversione int2string...
													 se avessi un compilatore cpp11 basterebbe
													 usare to_string()*/
													string contatore_stringa;          
													ostringstream convert;  
													convert << contatore;    
													contatore_stringa= convert.str();
													string nomeimmagine="immagine"+contatore_stringa+".jpg";
													scrivi("Salvataggio immagine numero "+contatore_stringa);
													imwrite(nomeimmagine,frame_pulito);
													break;
													}

								else if (key==int('n')) {
														scrivi("Frame scartato");
														trovata_scacchiera==false;
														break;
														}

								else continue;
													}
												}


						
							}/* chiuso while(1) ciclo più esterno*/
cap.release();

return(0);	
}








void scrivi(string messaggio){
	cout<<endl<<messaggio<<endl;
};