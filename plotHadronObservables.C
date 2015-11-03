//------------------------------------------
// Macro to plot hadronic v2 for d+Au
// collisions at a variety of beam
// energies, from 7.7 to 200 GeV.
//------------------------------------------
#include <iostream>

#include "TH2.h"
#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TGraphErrors.h"

using namespace std;

//------------------------------------------
// Variables
//------------------------------------------

//Number of data points
const int DATAPTS = 10;

TH2F *hv2_pT_5020GeV;
TH2F *hv2_pT_200GeV;
TH2F *hv2_pT_62GeV;
TH2F *hv2_pT_39GeV;
TH2F *hv2_pT_20GeV;
TH2F *hv2_pT_7GeV;

TH2F *hv3_pT_5020GeV;
TH2F *hv3_pT_200GeV;
TH2F *hv3_pT_62GeV;
TH2F *hv3_pT_39GeV;
TH2F *hv3_pT_20GeV;
TH2F *hv3_pT_7GeV;

TProfile *hv2_5020GeV;
TProfile *hv2_200GeV;
TProfile *hv2_62GeV;
TProfile *hv2_39GeV;
TProfile *hv2_20GeV;
TProfile *hv2_7GeV;

TProfile *hv3_5020GeV;
TProfile *hv3_200GeV;
TProfile *hv3_62GeV;
TProfile *hv3_39GeV;
TProfile *hv3_20GeV;
TProfile *hv3_7GeV;

//AMPT results
TGraphErrors *gv2_5020GeV;
TGraphErrors *gv2_200GeV;
TGraphErrors *gv2_62GeV;
TGraphErrors *gv2_39GeV;
TGraphErrors *gv2_20GeV;
TGraphErrors *gv2_7GeV;

TGraphErrors *gv3_5020GeV;
TGraphErrors *gv3_200GeV;
TGraphErrors *gv3_62GeV;
TGraphErrors *gv3_39GeV;
TGraphErrors *gv3_20GeV;
TGraphErrors *gv3_7GeV;

//Hydro results
// ---SONIC has no preflow
// ---superSONIC has preflow!
TGraphErrors *gv2_200GeV_sonic;
TGraphErrors *gv2_62GeV_sonic;
TGraphErrors *gv2_39GeV_sonic;
TGraphErrors *gv2_20GeV_sonic;
TGraphErrors *gv2_7GeV_sonic;

TGraphErrors *gv2_200GeV_supersonic;
TGraphErrors *gv2_62GeV_supersonic;
TGraphErrors *gv2_39GeV_supersonic;
TGraphErrors *gv2_20GeV_supersonic;
TGraphErrors *gv2_7GeV_supersonic;

TGraphErrors *gv3_200GeV_sonic;
TGraphErrors *gv3_62GeV_sonic;
TGraphErrors *gv3_39GeV_sonic;
TGraphErrors *gv3_20GeV_sonic;
TGraphErrors *gv3_7GeV_sonic;

TGraphErrors *gv3_200GeV_supersonic;
TGraphErrors *gv3_62GeV_supersonic;
TGraphErrors *gv3_39GeV_supersonic;
TGraphErrors *gv3_20GeV_supersonic;
TGraphErrors *gv3_7GeV_supersonic;

//Data PHENIX results
TGraphErrors *grmpcs2;
TGraphErrors *sgrmpcs2;
TBox *box[DATAPTS];


//------------------------------------------
// Functions
//------------------------------------------

void readFile()
{
	//AMPT results are read in as 2D histograms, and then projected to TProfiles
	TFile *fHadron_5020GeV = new TFile("ampt_dPb_BES_hadron.root");
	TFile *fHadron_200GeV = new TFile("ampt_dAu_BES_hadron_200GeV.root");
	TFile *fHadron_62GeV  = new TFile("ampt_dAu_BES_hadron_62GeV.root");
	TFile *fHadron_39GeV  = new TFile("ampt_dAu_BES_hadron_39GeV.root");
	TFile *fHadron_20GeV  = new TFile("ampt_dAu_BES_hadron_20GeV.root");
	TFile *fHadron_7GeV   = new TFile("ampt_dAu_BES_hadron_7GeV.root");

	hv2_pT_7GeV    = (TH2F*) fHadron_7GeV->Get("hv2_pT");
	hv2_pT_20GeV   = (TH2F*) fHadron_20GeV->Get("hv2_pT");
	hv2_pT_39GeV   = (TH2F*) fHadron_39GeV->Get("hv2_pT");
	hv2_pT_62GeV   = (TH2F*) fHadron_62GeV->Get("hv2_pT");
	hv2_pT_200GeV  = (TH2F*) fHadron_200GeV->Get("hv2_pT");
	hv2_pT_5020GeV = (TH2F*) fHadron_5020GeV->Get("hv2_pT");

	hv3_pT_7GeV    = (TH2F*) fHadron_7GeV->Get("hv3_pT");
	hv3_pT_20GeV   = (TH2F*) fHadron_20GeV->Get("hv3_pT");
	hv3_pT_39GeV   = (TH2F*) fHadron_39GeV->Get("hv3_pT");
	hv3_pT_62GeV   = (TH2F*) fHadron_62GeV->Get("hv3_pT");
	hv3_pT_200GeV  = (TH2F*) fHadron_200GeV->Get("hv3_pT");
	hv3_pT_5020GeV = (TH2F*) fHadron_5020GeV->Get("hv3_pT");

	//Hydro results are read in directly as TGraphErrors
	TFile *fSonic = new TFile("sonicPlots.root");

	gv2_7GeV_sonic = (TGraphErrors*) fSonic->Get("gv2_7GeV");
	gv2_20GeV_sonic = (TGraphErrors*) fSonic->Get("gv2_20GeV");
	gv2_39GeV_sonic = (TGraphErrors*) fSonic->Get("gv2_39GeV");
	gv2_62GeV_sonic = (TGraphErrors*) fSonic->Get("gv2_62GeV");
	gv2_200GeV_sonic = (TGraphErrors*) fSonic->Get("gv2_200GeV");

	gv2_7GeV_supersonic = (TGraphErrors*) fSonic->Get("gv2_7GeV_pf");
	gv2_20GeV_supersonic = (TGraphErrors*) fSonic->Get("gv2_20GeV_pf");
	gv2_39GeV_supersonic = (TGraphErrors*) fSonic->Get("gv2_39GeV_pf");
	gv2_62GeV_supersonic = (TGraphErrors*) fSonic->Get("gv2_62GeV_pf");
	gv2_200GeV_supersonic = (TGraphErrors*) fSonic->Get("gv2_200GeV_pf");

	gv3_7GeV_sonic = (TGraphErrors*) fSonic->Get("gv3_7GeV");
	gv3_20GeV_sonic = (TGraphErrors*) fSonic->Get("gv3_20GeV");
	gv3_39GeV_sonic = (TGraphErrors*) fSonic->Get("gv3_39GeV");
	gv3_62GeV_sonic = (TGraphErrors*) fSonic->Get("gv3_62GeV");
	gv3_200GeV_sonic = (TGraphErrors*) fSonic->Get("gv3_200GeV");

	gv3_7GeV_supersonic = (TGraphErrors*) fSonic->Get("gv3_7GeV_pf");
	gv3_20GeV_supersonic = (TGraphErrors*) fSonic->Get("gv3_20GeV_pf");
	gv3_39GeV_supersonic = (TGraphErrors*) fSonic->Get("gv3_39GeV_pf");
	gv3_62GeV_supersonic = (TGraphErrors*) fSonic->Get("gv3_62GeV_pf");
	gv3_200GeV_supersonic = (TGraphErrors*) fSonic->Get("gv3_200GeV_pf");

}

void extractAMPTvn()
{
	hv2_5020GeV = (TProfile*) hv2_pT_5020GeV->ProfileY("hv2_5020GeV");
	hv2_200GeV  = (TProfile*) hv2_pT_200GeV->ProfileY("hv2_200GeV");
	hv2_62GeV   = (TProfile*) hv2_pT_62GeV->ProfileY("hv2_62GeV");
	hv2_39GeV   = (TProfile*) hv2_pT_39GeV->ProfileY("hv2_39GeV");
	hv2_20GeV   = (TProfile*) hv2_pT_20GeV->ProfileY("hv2_20GeV");
	hv2_7GeV    = (TProfile*) hv2_pT_7GeV->ProfileY("hv2_7GeV");

	hv3_5020GeV = (TProfile*) hv3_pT_5020GeV->ProfileY("hv3_5020GeV");
	hv3_200GeV  = (TProfile*) hv3_pT_200GeV->ProfileY("hv3_200GeV");
	hv3_62GeV   = (TProfile*) hv3_pT_62GeV->ProfileY("hv3_62GeV");
	hv3_39GeV   = (TProfile*) hv3_pT_39GeV->ProfileY("hv3_39GeV");
	hv3_20GeV   = (TProfile*) hv3_pT_20GeV->ProfileY("hv3_20GeV");
	hv3_7GeV    = (TProfile*) hv3_pT_7GeV->ProfileY("hv3_7GeV");
}

void drawSeparateEnergies()
{
	//sqrt{s_{NN} = 7 GeV
	TCanvas *c1 = new TCanvas("c1","c1",600,600);
	gv2_7GeV->SetLineColor(kOrange+10);
	gv3_7GeV->SetLineColor(kAzure+7);
	gv2_7GeV_supersonic->SetLineColor(kOrange-3);
	gv3_7GeV_supersonic->SetLineColor(kViolet+9);

	gv2_7GeV->SetFillColorAlpha(kOrange+10,0.5);
	gv3_7GeV->SetFillColorAlpha(kAzure+7,0.5);
	gv2_7GeV_supersonic->SetFillColorAlpha(kOrange-3,0.5);
	gv3_7GeV_supersonic->SetFillColorAlpha(kViolet+9,0.5);

	gv2_7GeV->SetLineWidth(3);
	gv3_7GeV->SetLineWidth(3);
	gv2_7GeV_supersonic->SetLineWidth(3);
	gv3_7GeV_supersonic->SetLineWidth(3);

	gv2_7GeV_supersonic->Draw("ALE3");
	gv3_7GeV_supersonic->Draw("LE3,same");
	gv2_7GeV->Draw("LE3,same");
	gv3_7GeV->Draw("LE3,same");

	gv2_7GeV_supersonic->SetTitle("");
	gv2_7GeV_supersonic->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	gv2_7GeV_supersonic->GetXaxis()->SetTitleFont(62);
	gv2_7GeV_supersonic->GetXaxis()->SetLabelFont(62);
	gv2_7GeV_supersonic->GetXaxis()->SetTitleOffset(1.2);
	gv2_7GeV_supersonic->GetXaxis()->SetRangeUser(0.0, 3.0);

	gv2_7GeV_supersonic->GetYaxis()->SetTitle("v_{n}");
	gv2_7GeV_supersonic->GetYaxis()->SetTitleFont(62);
	gv2_7GeV_supersonic->GetYaxis()->SetLabelFont(62);
	gv2_7GeV_supersonic->GetYaxis()->SetTitleOffset(1.2);
	gv2_7GeV_supersonic->GetYaxis()->SetRangeUser(0.0, 0.189);

	TLatex *tlt7GeV = new TLatex(0.15,0.8,"d+Au at 7 GeV");
	tlt7GeV->SetNDC(kTRUE);
	tlt7GeV->Draw("same");

	TLegend *leg = new TLegend(0.15, 0.6, 0.42, 0.77);
	leg->AddEntry(gv2_7GeV_supersonic,"superSONIC v_{2}","LF");
	leg->AddEntry(gv3_7GeV_supersonic,"superSONIC v_{3}","LF");
	leg->AddEntry(gv2_7GeV,"AMPT v_{2}","LF");
	leg->AddEntry(gv3_7GeV,"AMPT v_{3}","LF");
	leg->SetLineColor(kWhite);
	leg->Draw("same");

	c1->SaveAs("Figures/Fig_dAu_vn_7GeV.pdf");

	//sqrt{s_{NN} = 20 GeV
	TCanvas *c2 = new TCanvas("c2","c2",600,600);
	gv2_20GeV->SetLineColor(kOrange+10);
	gv3_20GeV->SetLineColor(kAzure+7);
	gv2_20GeV_supersonic->SetLineColor(kOrange-3);
	gv3_20GeV_supersonic->SetLineColor(kViolet+9);

	gv2_20GeV->SetFillColorAlpha(kOrange+10,0.5);
	gv3_20GeV->SetFillColorAlpha(kAzure+7,0.5);
	gv2_20GeV_supersonic->SetFillColorAlpha(kOrange-3,0.5);
	gv3_20GeV_supersonic->SetFillColorAlpha(kViolet+9,0.5);

	gv2_20GeV->SetLineWidth(3);
	gv3_20GeV->SetLineWidth(3);
	gv2_20GeV_supersonic->SetLineWidth(3);
	gv3_20GeV_supersonic->SetLineWidth(3);

	gv2_20GeV_supersonic->Draw("ALE3");
	gv3_20GeV_supersonic->Draw("LE3,same");
	gv2_20GeV->Draw("LE3,same");
	gv3_20GeV->Draw("LE3,same");

	gv2_20GeV_supersonic->SetTitle("");
	gv2_20GeV_supersonic->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	gv2_20GeV_supersonic->GetXaxis()->SetTitleFont(62);
	gv2_20GeV_supersonic->GetXaxis()->SetLabelFont(62);
	gv2_20GeV_supersonic->GetXaxis()->SetTitleOffset(1.2);
	gv2_20GeV_supersonic->GetXaxis()->SetRangeUser(0.0, 3.0);

	gv2_20GeV_supersonic->GetYaxis()->SetTitle("v_{n}");
	gv2_20GeV_supersonic->GetYaxis()->SetTitleFont(62);
	gv2_20GeV_supersonic->GetYaxis()->SetLabelFont(62);
	gv2_20GeV_supersonic->GetYaxis()->SetTitleOffset(1.2);
	gv2_20GeV_supersonic->GetYaxis()->SetRangeUser(0.0, 0.189);

	TLatex *tlt20GeV = new TLatex(0.15,0.8,"d+Au at 20 GeV");
	tlt20GeV->SetNDC(kTRUE);
	tlt20GeV->Draw("same");

	TLegend *leg2 = new TLegend(0.15, 0.6, 0.42, 0.77);
	leg2->AddEntry(gv2_20GeV_supersonic,"superSONIC v_{2}","LF");
	leg2->AddEntry(gv3_20GeV_supersonic,"superSONIC v_{3}","LF");
	leg2->AddEntry(gv2_20GeV,"AMPT v_{2}","LF");
	leg2->AddEntry(gv3_20GeV,"AMPT v_{3}","LF");
	leg2->SetLineColor(kWhite);
	leg2->Draw("same");

	c2->SaveAs("Figures/Fig_dAu_vn_20GeV.pdf");

	//sqrt{s_{NN} = 39 GeV
	TCanvas *c3 = new TCanvas("c3","c3",600,600);
	gv2_39GeV->SetLineColor(kOrange+10);
	gv3_39GeV->SetLineColor(kAzure+7);
	gv2_39GeV_supersonic->SetLineColor(kOrange-3);
	gv3_39GeV_supersonic->SetLineColor(kViolet+9);

	gv2_39GeV->SetFillColorAlpha(kOrange+10,0.5);
	gv3_39GeV->SetFillColorAlpha(kAzure+7,0.5);
	gv2_39GeV_supersonic->SetFillColorAlpha(kOrange-3,0.5);
	gv3_39GeV_supersonic->SetFillColorAlpha(kViolet+9,0.5);

	gv2_39GeV->SetLineWidth(3);
	gv3_39GeV->SetLineWidth(3);
	gv2_39GeV_supersonic->SetLineWidth(3);
	gv3_39GeV_supersonic->SetLineWidth(3);

	gv2_39GeV_supersonic->Draw("ALE3");
	gv3_39GeV_supersonic->Draw("LE3,same");
	gv2_39GeV->Draw("LE3,same");
	gv3_39GeV->Draw("LE3,same");

	gv2_39GeV_supersonic->SetTitle("");
	gv2_39GeV_supersonic->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	gv2_39GeV_supersonic->GetXaxis()->SetTitleFont(62);
	gv2_39GeV_supersonic->GetXaxis()->SetLabelFont(62);
	gv2_39GeV_supersonic->GetXaxis()->SetTitleOffset(1.2);
	gv2_39GeV_supersonic->GetXaxis()->SetRangeUser(0.0, 3.0);

	gv2_39GeV_supersonic->GetYaxis()->SetTitle("v_{n}");
	gv2_39GeV_supersonic->GetYaxis()->SetTitleFont(62);
	gv2_39GeV_supersonic->GetYaxis()->SetLabelFont(62);
	gv2_39GeV_supersonic->GetYaxis()->SetTitleOffset(1.2);
	gv2_39GeV_supersonic->GetYaxis()->SetRangeUser(0.0, 0.189);

	TLatex *tlt39GeV = new TLatex(0.15,0.8,"d+Au at 39 GeV");
	tlt39GeV->SetNDC(kTRUE);
	tlt39GeV->Draw("same");

	TLegend *leg3 = new TLegend(0.15, 0.6, 0.42, 0.77);
	leg3->AddEntry(gv2_39GeV_supersonic,"superSONIC v_{2}","LF");
	leg3->AddEntry(gv3_39GeV_supersonic,"superSONIC v_{3}","LF");
	leg3->AddEntry(gv2_39GeV,"AMPT v_{2}","LF");
	leg3->AddEntry(gv3_39GeV,"AMPT v_{3}","LF");
	leg3->SetLineColor(kWhite);
	leg3->Draw("same");

	c3->SaveAs("Figures/Fig_dAu_vn_39GeV.pdf");

	//sqrt{s_{NN} = 62 GeV
	TCanvas *c4 = new TCanvas("c4","c4",600,600);
	gv2_62GeV->SetLineColor(kOrange+10);
	gv3_62GeV->SetLineColor(kAzure+7);
	gv2_62GeV_supersonic->SetLineColor(kOrange-3);
	gv3_62GeV_supersonic->SetLineColor(kViolet+9);

	gv2_62GeV->SetFillColorAlpha(kOrange+10,0.5);
	gv3_62GeV->SetFillColorAlpha(kAzure+7,0.5);
	gv2_62GeV_supersonic->SetFillColorAlpha(kOrange-3,0.5);
	gv3_62GeV_supersonic->SetFillColorAlpha(kViolet+9,0.5);

	gv2_62GeV->SetLineWidth(3);
	gv3_62GeV->SetLineWidth(3);
	gv2_62GeV_supersonic->SetLineWidth(3);
	gv3_62GeV_supersonic->SetLineWidth(3);

	gv2_62GeV_supersonic->Draw("ALE3");
	gv3_62GeV_supersonic->Draw("LE3,same");
	gv2_62GeV->Draw("LE3,same");
	gv3_62GeV->Draw("LE3,same");

	gv2_62GeV_supersonic->SetTitle("");
	gv2_62GeV_supersonic->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	gv2_62GeV_supersonic->GetXaxis()->SetTitleFont(62);
	gv2_62GeV_supersonic->GetXaxis()->SetLabelFont(62);
	gv2_62GeV_supersonic->GetXaxis()->SetTitleOffset(1.2);
	gv2_62GeV_supersonic->GetXaxis()->SetRangeUser(0.0, 3.0);

	gv2_62GeV_supersonic->GetYaxis()->SetTitle("v_{n}");
	gv2_62GeV_supersonic->GetYaxis()->SetTitleFont(62);
	gv2_62GeV_supersonic->GetYaxis()->SetLabelFont(62);
	gv2_62GeV_supersonic->GetYaxis()->SetTitleOffset(1.2);
	gv2_62GeV_supersonic->GetYaxis()->SetRangeUser(0.0, 0.189);

	TLatex *tlt62GeV = new TLatex(0.15,0.8,"d+Au at 62.4 GeV");
	tlt62GeV->SetNDC(kTRUE);
	tlt62GeV->Draw("same");

	TLegend *leg4 = new TLegend(0.15, 0.6, 0.42, 0.77);
	leg4->AddEntry(gv2_62GeV_supersonic,"superSONIC v_{2}","LF");
	leg4->AddEntry(gv3_62GeV_supersonic,"superSONIC v_{3}","LF");
	leg4->AddEntry(gv2_62GeV,"AMPT v_{2}","LF");
	leg4->AddEntry(gv3_62GeV,"AMPT v_{3}","LF");
	leg4->SetLineColor(kWhite);
	leg4->Draw("same");

	c4->SaveAs("Figures/Fig_dAu_vn_62GeV.pdf");

	//sqrt{s_{NN} = 200 GeV
	TCanvas *c5 = new TCanvas("c5","c5",600,600);
	gv2_200GeV->SetLineColor(kOrange+10);
	gv3_200GeV->SetLineColor(kAzure+7);
	gv2_200GeV_supersonic->SetLineColor(kOrange-3);
	gv3_200GeV_supersonic->SetLineColor(kViolet+9);

	gv2_200GeV->SetFillColorAlpha(kOrange+10,0.5);
	gv3_200GeV->SetFillColorAlpha(kAzure+7,0.5);
	gv2_200GeV_supersonic->SetFillColorAlpha(kOrange-3,0.5);
	gv3_200GeV_supersonic->SetFillColorAlpha(kViolet+9,0.5);

	gv2_200GeV->SetLineWidth(3);
	gv3_200GeV->SetLineWidth(3);
	gv2_200GeV_supersonic->SetLineWidth(3);

	gv2_200GeV_supersonic->Draw("ALE3");
	gv3_200GeV_supersonic->Draw("LE3,same");
	gv2_200GeV->Draw("LE3,same");
	gv3_200GeV->Draw("LE3,same");

	gv2_200GeV_supersonic->SetTitle("");
	gv2_200GeV_supersonic->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	gv2_200GeV_supersonic->GetXaxis()->SetTitleFont(62);
	gv2_200GeV_supersonic->GetXaxis()->SetLabelFont(62);
	gv2_200GeV_supersonic->GetXaxis()->SetTitleOffset(1.2);
	gv2_200GeV_supersonic->GetXaxis()->SetRangeUser(0.0, 3.0);

	gv2_200GeV_supersonic->GetYaxis()->SetTitle("v_{n}");
	gv2_200GeV_supersonic->GetYaxis()->SetTitleFont(62);
	gv2_200GeV_supersonic->GetYaxis()->SetLabelFont(62);
	gv2_200GeV_supersonic->GetYaxis()->SetTitleOffset(1.2);
	gv2_200GeV_supersonic->GetYaxis()->SetRangeUser(0.0, 0.189);

	TLatex *tlt200GeV = new TLatex(0.15,0.8,"d+Au at 200 GeV");
	tlt200GeV->SetNDC(kTRUE);
	tlt200GeV->Draw("same");

	TLegend *leg5 = new TLegend(0.15, 0.6, 0.42, 0.77);
	leg5->AddEntry(gv2_200GeV_supersonic,"superSONIC v_{2}","LF");
	leg5->AddEntry(gv3_200GeV_supersonic,"superSONIC v_{3}","LF");
	leg5->AddEntry(gv2_200GeV,"AMPT v_{2}","LF");
	leg5->AddEntry(gv3_200GeV,"AMPT v_{3}","LF");
	leg5->AddEntry(grmpcs2,"PHENIX v_{2}","P");
	leg5->SetLineColor(kWhite);
	leg5->Draw("same");

	//Draw data points
	grmpcs2->SetMarkerStyle(21);
	grmpcs2->SetMarkerColor(kBlack);
	grmpcs2->SetLineColor(kBlack);
	grmpcs2->Draw("P,same");

    //Draw systematic error boxes for v2
	for(int i=0; i<DATAPTS; i++)
	{
		box[i]->SetFillColor(kBlack);
		box[i]->SetFillStyle(0);
		box[i]->SetLineColor(kBlack);
		box[i]->SetLineWidth(1);
		box[i]->Draw("LSAME");
	}

	c5->SaveAs("Figures/Fig_dAu_vn_200GeV.pdf");

	//d+Pb at sqrt{s_{NN} = 5020 GeV
	TCanvas *c6 = new TCanvas("c6","c6",600,600);
	gv2_5020GeV->SetLineColor(kOrange+10);
	gv3_5020GeV->SetLineColor(kAzure+7);
	//gv2_5020GeV_supersonic->SetLineColor(kOrange-3);
	//gv3_5020GeV_supersonic->SetLineColor(kViolet+9);

	gv2_5020GeV->SetFillColorAlpha(kOrange+10,0.5);
	gv3_5020GeV->SetFillColorAlpha(kAzure+7,0.5);
	//gv2_5020GeV_supersonic->SetFillColorAlpha(kOrange-3,0.5);
	//gv3_5020GeV_supersonic->SetFillColorAlpha(kViolet+9,0.5);

	gv2_5020GeV->SetLineWidth(3);
	gv3_5020GeV->SetLineWidth(3);
	//gv2_5020GeV_supersonic->SetLineWidth(3);
	//gv3_5020GeV_supersonic->SetLineWidth(3);

	//gv2_5020GeV_supersonic->Draw("ALE3");
	//gv3_5020GeV_supersonic->Draw("LE3,same");
	gv2_5020GeV->Draw("ALE3");
	gv3_5020GeV->Draw("LE3,same");

	gv2_5020GeV->SetTitle("");
	gv2_5020GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	gv2_5020GeV->GetXaxis()->SetTitleFont(62);
	gv2_5020GeV->GetXaxis()->SetLabelFont(62);
	gv2_5020GeV->GetXaxis()->SetTitleOffset(1.2);
	gv2_5020GeV->GetXaxis()->SetRangeUser(0.0, 3.0);

	gv2_5020GeV->GetYaxis()->SetTitle("v_{n}");
	gv2_5020GeV->GetYaxis()->SetTitleFont(62);
	gv2_5020GeV->GetYaxis()->SetLabelFont(62);
	gv2_5020GeV->GetYaxis()->SetTitleOffset(1.2);
	gv2_5020GeV->GetYaxis()->SetRangeUser(0.0, 0.189);

	TLatex *tlt5020GeV = new TLatex(0.15,0.8,"d+Pb at 5.02 TeV");
	tlt5020GeV->SetNDC(kTRUE);
	tlt5020GeV->Draw("same");

	TLegend *leg6 = new TLegend(0.15, 0.6, 0.42, 0.77);
	//leg6->AddEntry(gv2_7GeV_supersonic,"superSONIC v_{2}","LF");
	//leg6->AddEntry(gv3_7GeV_supersonic,"superSONIC v_{3}","LF");
	leg6->AddEntry(gv2_5020GeV,"AMPT v_{2}","LF");
	leg6->AddEntry(gv3_5020GeV,"AMPT v_{3}","LF");
	leg6->SetLineColor(kWhite);
	leg6->Draw("same");

	c6->SaveAs("Figures/Fig_dPb_vn_5020GeV.pdf");
}

void draw_v2()
{
	gStyle->SetOptStat(0);

	TCanvas *c = new TCanvas("c","c",600,600);

	gv2_200GeV->SetLineColor(kRed+1);
	gv2_62GeV->SetLineColor(kOrange+7);
	gv2_39GeV->SetLineColor(kSpring-1);
	gv2_20GeV->SetLineColor(kAzure+7-3);
	gv2_7GeV->SetLineColor(kViolet+1);

	gv2_200GeV_sonic->SetLineColor(kRed);
	gv2_62GeV_sonic->SetLineColor(kOrange);
	gv2_39GeV_sonic->SetLineColor(kSpring-9);
	gv2_20GeV_sonic->SetLineColor(kAzure+7+8);
	gv2_7GeV_sonic->SetLineColor(kViolet-2);

	gv2_200GeV_supersonic->SetLineColor(kRed);
	gv2_62GeV_supersonic->SetLineColor(kOrange);
	gv2_39GeV_supersonic->SetLineColor(kSpring-9);
	gv2_20GeV_supersonic->SetLineColor(kAzure+7+8);
	gv2_7GeV_supersonic->SetLineColor(kViolet-2);

	gv2_200GeV->SetLineWidth(2);
	gv2_62GeV->SetLineWidth(2);
	gv2_39GeV->SetLineWidth(2);
	gv2_20GeV->SetLineWidth(2);
	gv2_7GeV->SetLineWidth(2);

	gv2_200GeV->SetFillColorAlpha(kRed+1,0.5);
	gv2_62GeV->SetFillColorAlpha(kOrange+7,0.5);
	gv2_39GeV->SetFillColorAlpha(kSpring-1,0.5);
	gv2_20GeV->SetFillColorAlpha(kAzure+7-3,0.5);
	gv2_7GeV->SetFillColorAlpha(kViolet+1,0.5);

	gv2_200GeV_sonic->SetFillColorAlpha(kRed,0.5);
	gv2_62GeV_sonic->SetFillColorAlpha(kOrange,0.5);
	gv2_39GeV_sonic->SetFillColorAlpha(kSpring-9,0.5);
	gv2_20GeV_sonic->SetFillColorAlpha(kAzure+7+8,0.5);
	gv2_7GeV_sonic->SetFillColorAlpha(kViolet-2,0.5);

	gv2_200GeV_supersonic->SetFillColorAlpha(kRed,0.5);
	gv2_62GeV_supersonic->SetFillColorAlpha(kOrange,0.5);
	gv2_39GeV_supersonic->SetFillColorAlpha(kSpring-9,0.5);
	gv2_20GeV_supersonic->SetFillColorAlpha(kAzure+7+8,0.5);
	gv2_7GeV_supersonic->SetFillColorAlpha(kViolet-2,0.5);

    gv2_200GeV->SetTitle("");
	gv2_200GeV->Draw("ALE3");
	gv2_62GeV->Draw("LE3,same");
	gv2_39GeV->Draw("LE3,same");
	gv2_20GeV->Draw("LE3,same");
	gv2_7GeV->Draw("LE3,same");

/*
	gv2_200GeV_sonic->Draw("LE3,same");
	gv2_62GeV_sonic->Draw("LE3,same");
	gv2_39GeV_sonic->Draw("LE3,same");
	gv2_20GeV_sonic->Draw("LE3,same");
	gv2_7GeV_sonic->Draw("LE3,same");
*/

	gv2_200GeV_supersonic->Draw("LE3,same");
	gv2_62GeV_supersonic->Draw("LE3,same");
	gv2_39GeV_supersonic->Draw("LE3,same");
	gv2_20GeV_supersonic->Draw("LE3,same");
	gv2_7GeV_supersonic->Draw("LE3,same");

	gv2_200GeV->GetXaxis()->SetRangeUser(0, 1.8);
	gv2_200GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");

	gv2_200GeV->GetYaxis()->SetRangeUser(0, 0.135);
	gv2_200GeV->GetYaxis()->SetTitle("v_{2}");

	TLegend *leg = new TLegend(0.5, 0.2, 0.8, 0.4);
	leg->AddEntry(gv2_200GeV,"AMPT 200 GeV","LF");
	leg->AddEntry(gv2_62GeV,"AMPT 62 GeV","LF");
	leg->AddEntry(gv2_39GeV,"AMPT 39 GeV","LF");
	leg->AddEntry(gv2_20GeV,"AMPT 20 GeV","LF");
	leg->AddEntry(gv2_7GeV,"AMPT 7.7 GeV","LF");
	leg->SetLineColor(kWhite);
	leg->Draw("same");
}

void createTGraphs()
{
	//First produce graphs for v2
	hv2_5020GeV->Rebin(2);
	hv2_200GeV->Rebin(2);
    hv2_62GeV->Rebin(2);
    hv2_39GeV->Rebin(2);
    hv2_20GeV->Rebin(2);
    hv2_7GeV->Rebin(2);

	const int nbins = 10;

	float x_5020GeV[nbins];
	float x_200GeV[nbins];
	float x_62GeV[nbins];
	float x_39GeV[nbins];
	float x_20GeV[nbins];
	float x_7GeV[nbins];

	float y_5020GeV[nbins];
	float y_200GeV[nbins];
	float y_62GeV[nbins];
	float y_39GeV[nbins];
	float y_20GeV[nbins];
	float y_7GeV[nbins];

	float xerr[nbins];

	float yerr_5020GeV[nbins];
	float yerr_200GeV[nbins];
	float yerr_62GeV[nbins];
	float yerr_39GeV[nbins];
	float yerr_20GeV[nbins];
	float yerr_7GeV[nbins];	

	for(int i=0; i<nbins; i++)
	{
		x_5020GeV[i] = hv2_5020GeV->GetBinCenter(i+1);
		x_200GeV[i] = hv2_200GeV->GetBinCenter(i+1);
		x_62GeV[i] = hv2_62GeV->GetBinCenter(i+1);
		x_39GeV[i] = hv2_39GeV->GetBinCenter(i+1);
		x_20GeV[i] = hv2_20GeV->GetBinCenter(i+1);
		x_7GeV[i] = hv2_7GeV->GetBinCenter(i+1);

		y_5020GeV[i] = hv2_5020GeV->GetBinContent(i+1);
		y_200GeV[i] = hv2_200GeV->GetBinContent(i+1);
		y_62GeV[i] = hv2_62GeV->GetBinContent(i+1);
		y_39GeV[i] = hv2_39GeV->GetBinContent(i+1);
		y_20GeV[i] = hv2_20GeV->GetBinContent(i+1);
		y_7GeV[i] = hv2_7GeV->GetBinContent(i+1);

		yerr_5020GeV[i] = hv2_5020GeV->GetBinError(i+1);
		yerr_200GeV[i] = hv2_200GeV->GetBinError(i+1);
		yerr_62GeV[i] = hv2_62GeV->GetBinError(i+1);
		yerr_39GeV[i] = hv2_39GeV->GetBinError(i+1);
		yerr_20GeV[i] = hv2_20GeV->GetBinError(i+1);
		yerr_7GeV[i] = hv2_7GeV->GetBinError(i+1);

		xerr[i] = 0;
	}

	gv2_5020GeV = new TGraphErrors(nbins,x_5020GeV,y_5020GeV,xerr,yerr_5020GeV);
	gv2_200GeV = new TGraphErrors(nbins,x_200GeV,y_200GeV,xerr,yerr_200GeV);
	gv2_62GeV  = new TGraphErrors(nbins,x_62GeV,y_62GeV,xerr,yerr_62GeV);
	gv2_39GeV  = new TGraphErrors(nbins,x_39GeV,y_39GeV,xerr,yerr_39GeV);
	gv2_20GeV  = new TGraphErrors(nbins,x_20GeV,y_20GeV,xerr,yerr_20GeV);
	gv2_7GeV   = new TGraphErrors(nbins,x_7GeV,y_7GeV,xerr,yerr_7GeV);

	//Now make graphs for v3
	hv3_5020GeV->Rebin(2);
	hv3_200GeV->Rebin(2);
    hv3_62GeV->Rebin(2);
    hv3_39GeV->Rebin(2);
    hv3_20GeV->Rebin(2);
    hv3_7GeV->Rebin(2);

	for(int i=0; i<nbins; i++)
	{
		x_5020GeV[i] = hv3_5020GeV->GetBinCenter(i+1);
		x_200GeV[i] = hv3_200GeV->GetBinCenter(i+1);
		x_62GeV[i] = hv3_62GeV->GetBinCenter(i+1);
		x_39GeV[i] = hv3_39GeV->GetBinCenter(i+1);
		x_20GeV[i] = hv3_20GeV->GetBinCenter(i+1);
		x_7GeV[i] = hv3_7GeV->GetBinCenter(i+1);

		y_5020GeV[i] = hv3_5020GeV->GetBinContent(i+1);
		y_200GeV[i] = hv3_200GeV->GetBinContent(i+1);
		y_62GeV[i] = hv3_62GeV->GetBinContent(i+1);
		y_39GeV[i] = hv3_39GeV->GetBinContent(i+1);
		y_20GeV[i] = hv3_20GeV->GetBinContent(i+1);
		y_7GeV[i] = hv3_7GeV->GetBinContent(i+1);

		yerr_5020GeV[i] = hv3_5020GeV->GetBinError(i+1);
		yerr_200GeV[i] = hv3_200GeV->GetBinError(i+1);
		yerr_62GeV[i] = hv3_62GeV->GetBinError(i+1);
		yerr_39GeV[i] = hv3_39GeV->GetBinError(i+1);
		yerr_20GeV[i] = hv3_20GeV->GetBinError(i+1);
		yerr_7GeV[i] = hv3_7GeV->GetBinError(i+1);

		xerr[i] = 0;
	}

	gv3_5020GeV = new TGraphErrors(nbins,x_5020GeV,y_5020GeV,xerr,yerr_5020GeV);
	gv3_200GeV = new TGraphErrors(nbins,x_200GeV,y_200GeV,xerr,yerr_200GeV);
	gv3_62GeV  = new TGraphErrors(nbins,x_62GeV,y_62GeV,xerr,yerr_62GeV);
	gv3_39GeV  = new TGraphErrors(nbins,x_39GeV,y_39GeV,xerr,yerr_39GeV);
	gv3_20GeV  = new TGraphErrors(nbins,x_20GeV,y_20GeV,xerr,yerr_20GeV);
	gv3_7GeV   = new TGraphErrors(nbins,x_7GeV,y_7GeV,xerr,yerr_7GeV);
}

void createDataTGraphs()
{
	float ptv2[24];
	float eptv2[24], sptv2[24];
	float v2mpcs[24], ev2mpcs[24], sv2mpcs[24], asv2mpcs1[24];

	ifstream finv2("v2_pt_dAu_00_05_sys.dat");

  	//Elliptic flow
	for(int i=0; i<DATAPTS; i++)
	{
		eptv2[i]=0;
		sptv2[i]=0.05;
    	finv2>>ptv2[i]>>v2mpcs[i]>>ev2mpcs[i]>>sv2mpcs[i];//>>asv2mpcs1[i];
  	}

  finv2.close();

  grmpcs2 = new TGraphErrors(DATAPTS, ptv2, v2mpcs, eptv2, ev2mpcs);
  sgrmpcs2 = new TGraphErrors(DATAPTS, ptv2, v2mpcs, sptv2, sv2mpcs);

  for(int i=0; i<DATAPTS; i++)
	{
		double px1 = ptv2[i]-0.05;
		double py1 = v2mpcs[i]+sv2mpcs[i];
		double px2 = ptv2[i]+0.05;
		double py2 = v2mpcs[i]-sv2mpcs[i];
		box[i] = new TBox(px1,py1,px2,py2);
	}
}

void plotHadronObservables()
{
	readFile();
	extractAMPTvn();
	createTGraphs();
	createDataTGraphs();
	drawSeparateEnergies();
}