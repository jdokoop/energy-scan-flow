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
#include "TLegend.h"
#include "TProfile.h"
#include "TGraphErrors.h"

using namespace std;

//------------------------------------------
// Variables
//------------------------------------------

TH2F *hv2_pT_200GeV;
TH2F *hv2_pT_62GeV;
TH2F *hv2_pT_39GeV;
TH2F *hv2_pT_20GeV;
TH2F *hv2_pT_7GeV;

TProfile *hv2_200GeV;
TProfile *hv2_62GeV;
TProfile *hv2_39GeV;
TProfile *hv2_20GeV;
TProfile *hv2_7GeV;

TGraphErrors *gv2_200GeV;
TGraphErrors *gv2_62GeV;
TGraphErrors *gv2_39GeV;
TGraphErrors *gv2_20GeV;
TGraphErrors *gv2_7GeV;

//------------------------------------------
// Functions
//------------------------------------------

void readFile()
{
	TFile *fHadron_200GeV = new TFile("ampt_dAu_BES_hadron_200GeV.root");
	TFile *fHadron_62GeV  = new TFile("ampt_dAu_BES_hadron_62GeV.root");
	TFile *fHadron_39GeV  = new TFile("ampt_dAu_BES_hadron_39GeV.root");
	TFile *fHadron_20GeV  = new TFile("ampt_dAu_BES_hadron_20GeV.root");
	TFile *fHadron_7GeV   = new TFile("ampt_dAu_BES_hadron_7GeV.root");

	hv2_pT_7GeV   = (TH2F*) fHadron_7GeV->Get("hv3_pT");
	hv2_pT_20GeV  = (TH2F*) fHadron_20GeV->Get("hv3_pT");
	hv2_pT_39GeV  = (TH2F*) fHadron_39GeV->Get("hv3_pT");
	hv2_pT_62GeV  = (TH2F*) fHadron_62GeV->Get("hv3_pT");
	hv2_pT_200GeV = (TH2F*) fHadron_200GeV->Get("hv3_pT");
}

void extract_v2()
{
	hv2_200GeV = (TProfile*) hv2_pT_200GeV->ProfileY("hv2_200GeV");
	hv2_62GeV  = (TProfile*) hv2_pT_62GeV->ProfileY("hv2_62GeV");
	hv2_39GeV  = (TProfile*) hv2_pT_39GeV->ProfileY("hv2_39GeV");
	hv2_20GeV  = (TProfile*) hv2_pT_20GeV->ProfileY("hv2_20GeV");
	hv2_7GeV   = (TProfile*) hv2_pT_7GeV->ProfileY("hv2_7GeV");
}

void draw_v2()
{
	gStyle->SetOptStat(0);

	TCanvas *c = new TCanvas("c","c",600,600);

	gv2_200GeV->SetLineColor(kRed+1);
	gv2_62GeV->SetLineColor(kOrange+7);
	gv2_39GeV->SetLineColor(kSpring-1);
	gv2_20GeV->SetLineColor(kAzure-3);
	gv2_7GeV->SetLineColor(kViolet+1);

	gv2_200GeV->SetLineWidth(2);
	gv2_62GeV->SetLineWidth(2);
	gv2_39GeV->SetLineWidth(2);
	gv2_20GeV->SetLineWidth(2);
	gv2_7GeV->SetLineWidth(2);

	gv2_200GeV->SetFillColorAlpha(kRed+1,0.5);
	gv2_62GeV->SetFillColorAlpha(kOrange+7,0.5);
	gv2_39GeV->SetFillColorAlpha(kSpring-1,0.5);
	gv2_20GeV->SetFillColorAlpha(kAzure-3,0.5);
	gv2_7GeV->SetFillColorAlpha(kViolet+1,0.5);

    gv2_200GeV->SetTitle("");
	gv2_200GeV->Draw("ALE3");
	gv2_62GeV->Draw("LE3,same");
	gv2_39GeV->Draw("LE3,same");
	gv2_20GeV->Draw("LE3,same");
	gv2_7GeV->Draw("LE3,same");

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
	hv2_200GeV->Rebin(2);
    hv2_62GeV->Rebin(2);
    hv2_39GeV->Rebin(2);
    hv2_20GeV->Rebin(2);
    hv2_7GeV->Rebin(2);

	const int nbins = 10;

	float x_200GeV[nbins];
	float x_62GeV[nbins];
	float x_39GeV[nbins];
	float x_20GeV[nbins];
	float x_7GeV[nbins];

	float y_200GeV[nbins];
	float y_62GeV[nbins];
	float y_39GeV[nbins];
	float y_20GeV[nbins];
	float y_7GeV[nbins];

	float xerr[nbins];

	float yerr_200GeV[nbins];
	float yerr_62GeV[nbins];
	float yerr_39GeV[nbins];
	float yerr_20GeV[nbins];
	float yerr_7GeV[nbins];	

	for(int i=0; i<nbins; i++)
	{
		x_200GeV[i] = hv2_200GeV->GetBinCenter(i+1);
		x_62GeV[i] = hv2_62GeV->GetBinCenter(i+1);
		x_39GeV[i] = hv2_39GeV->GetBinCenter(i+1);
		x_20GeV[i] = hv2_20GeV->GetBinCenter(i+1);
		x_7GeV[i] = hv2_7GeV->GetBinCenter(i+1);

		y_200GeV[i] = hv2_200GeV->GetBinContent(i+1);
		y_62GeV[i] = hv2_62GeV->GetBinContent(i+1);
		y_39GeV[i] = hv2_39GeV->GetBinContent(i+1);
		y_20GeV[i] = hv2_20GeV->GetBinContent(i+1);
		y_7GeV[i] = hv2_7GeV->GetBinContent(i+1);

		yerr_200GeV[i] = hv2_200GeV->GetBinError(i+1);
		yerr_62GeV[i] = hv2_62GeV->GetBinError(i+1);
		yerr_39GeV[i] = hv2_39GeV->GetBinError(i+1);
		yerr_20GeV[i] = hv2_20GeV->GetBinError(i+1);
		yerr_7GeV[i] = hv2_7GeV->GetBinError(i+1);

		xerr[i] = 0;
	}

	gv2_200GeV = new TGraphErrors(nbins,x_200GeV,y_200GeV,xerr,yerr_200GeV);
	gv2_62GeV  = new TGraphErrors(nbins,x_62GeV,y_62GeV,xerr,yerr_62GeV);
	gv2_39GeV  = new TGraphErrors(nbins,x_39GeV,y_39GeV,xerr,yerr_39GeV);
	gv2_20GeV  = new TGraphErrors(nbins,x_20GeV,y_20GeV,xerr,yerr_20GeV);
	gv2_7GeV   = new TGraphErrors(nbins,x_7GeV,y_7GeV,xerr,yerr_7GeV);

}

void plotHadronObservables()
{
	readFile();
	extract_v2();
	createTGraphs();
	draw_v2();
}