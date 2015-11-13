//------------------------------------------
// Macro to plot partonic v2 for d+Au
// collisions at a variety of beam
// energies, from 7.7 to 200 GeV.
//------------------------------------------
#include <iostream>

#include "TH2.h"
#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TGraphErrors.h"

using namespace std;

//------------------------------------------
// Variables
//------------------------------------------

const int NENERGY = 6; //5 collision energy values

TH1F *hNscatt[NENERGY];
TProfile *hv2_pT[NENERGY];

//------------------------------------------
// Functions
//------------------------------------------

void readFile()
{
	TFile *f5020GeV = new TFile("ampt_dPb_BES_parton.root");
	TFile *f200GeV = new TFile("ampt_dAu_BES_parton_200GeV.root");
	TFile *f62GeV  = new TFile("ampt_dAu_BES_parton_62GeV.root");
	TFile *f39GeV  = new TFile("ampt_dAu_BES_parton_39GeV.root");
	TFile *f20GeV  = new TFile("ampt_dAu_BES_parton_20GeV.root");
	TFile *f7GeV   = new TFile("ampt_dAu_BES_parton_7GeV.root");

	hNscatt[0] = (TH1F*) f200GeV->Get("hNscatt");
	hNscatt[1] = (TH1F*) f62GeV->Get("hNscatt");
	hNscatt[2] = (TH1F*) f39GeV->Get("hNscatt");
	hNscatt[3] = (TH1F*) f20GeV->Get("hNscatt");
	hNscatt[4] = (TH1F*) f7GeV->Get("hNscatt");
	hNscatt[5] = (TH1F*) f5020GeV->Get("hNscatt");

	hv2_pT[0] = (TProfile*) f200GeV->Get("hv2_pT_0");
	hv2_pT[1] = (TProfile*) f62GeV->Get("hv2_pT_0");
	hv2_pT[2] = (TProfile*) f39GeV->Get("hv2_pT_0");
	hv2_pT[3] = (TProfile*) f20GeV->Get("hv2_pT_0");
	hv2_pT[4] = (TProfile*) f7GeV->Get("hv2_pT_0");
	hv2_pT[5] = (TProfile*) f5020GeV->Get("hv2_pT_0");
}

void drawNscatt()
{
	gStyle->SetOptStat(0);
	TCanvas *c1 = new TCanvas("c1","c1",700,700);
	c1->SetTickx();
	c1->SetTicky();

	hNscatt[0]->Scale(1.0/hNscatt[0]->Integral());
	hNscatt[1]->Scale(1.0/hNscatt[1]->Integral());
	hNscatt[2]->Scale(1.0/hNscatt[2]->Integral());
	hNscatt[3]->Scale(1.0/hNscatt[3]->Integral());
	hNscatt[4]->Scale(1.0/hNscatt[4]->Integral());
	hNscatt[5]->Scale(1.0/hNscatt[5]->Integral());

	hNscatt[0]->SetLineColor(kRed+1);
	hNscatt[1]->SetLineColor(kOrange+7);
	hNscatt[2]->SetLineColor(kSpring-1);
	hNscatt[3]->SetLineColor(kAzure-3);
	hNscatt[4]->SetLineColor(kViolet+1);
	hNscatt[5]->SetLineColor(kBlack);

	hNscatt[0]->SetMarkerColor(kRed+1);
	hNscatt[1]->SetMarkerColor(kOrange+7);
	hNscatt[2]->SetMarkerColor(kSpring-1);
	hNscatt[3]->SetMarkerColor(kAzure-3);
	hNscatt[4]->SetMarkerColor(kViolet+1);
	hNscatt[5]->SetMarkerColor(kBlack);

	hNscatt[0]->SetMarkerStyle(3);
	hNscatt[1]->SetMarkerStyle(3);
	hNscatt[2]->SetMarkerStyle(3);
	hNscatt[3]->SetMarkerStyle(3);
	hNscatt[4]->SetMarkerStyle(3);
	hNscatt[5]->SetMarkerStyle(3);

	hNscatt[0]->SetLineWidth(2);
	hNscatt[1]->SetLineWidth(2);
	hNscatt[2]->SetLineWidth(2);
	hNscatt[3]->SetLineWidth(2);
	hNscatt[4]->SetLineWidth(2);
	hNscatt[5]->SetLineWidth(2);

	hNscatt[0]->SetTitle("");
	hNscatt[0]->GetXaxis()->SetTitle("N_{scatt}");
	hNscatt[0]->GetXaxis()->SetTitleOffset(1.2);
	hNscatt[0]->GetXaxis()->SetTitleFont(62);
	hNscatt[0]->GetXaxis()->SetLabelFont(62);

	hNscatt[0]->GetYaxis()->SetTitle("Probability");
	hNscatt[0]->GetYaxis()->SetTitleOffset(1.3);
	hNscatt[0]->GetYaxis()->SetRangeUser(-0.02,0.75);
	hNscatt[0]->GetYaxis()->SetTitleFont(62);
	hNscatt[0]->GetYaxis()->SetLabelFont(62);

	hNscatt[0]->Draw("CP");
	hNscatt[1]->Draw("CP,same");
	hNscatt[2]->Draw("CP,same");
	hNscatt[3]->Draw("CP,same");
	hNscatt[4]->Draw("CP,same");
	hNscatt[5]->Draw("LP,same");

	TLegend *leg = new TLegend(0.5, 0.5, 0.8, 0.8);
	leg->AddEntry(hNscatt[5],"AMPT d+Pb 5.02 TeV","LP");
	leg->AddEntry(hNscatt[0],"AMPT d+Au 200 GeV","LP");
	leg->AddEntry(hNscatt[1],"AMPT d+Au 62 GeV","LP");
	leg->AddEntry(hNscatt[2],"AMPT d+Au 39 GeV","LP");
	leg->AddEntry(hNscatt[3],"AMPT d+Au 20 GeV","LP");
	leg->AddEntry(hNscatt[4],"AMPT d+Au 7.7 GeV","LP");
	leg->SetLineColor(kWhite);
	leg->Draw("same");
}

void drawv2()
{
	//Make TGraphs out of TProfiles
	const int nbins = hv2_pT[0]->GetNbinsX();

	float xvals[nbins];

	float y200[nbins];
	float y62[nbins];
	float y39[nbins];
	float y20[nbins];
	float y7[nbins];

	for(int i=0; i<nbins; i++)
	{
		xvals[i] = hv2_pT[0]->GetBinCenter(i+1);

		y200[i] = hv2_pT[0]->GetBinContent(i+1);
		y62[i]  = hv2_pT[1]->GetBinContent(i+1);
		y39[i]  = hv2_pT[2]->GetBinContent(i+1);
		y20[i]  = hv2_pT[3]->GetBinContent(i+1);
		y7[i]   = hv2_pT[4]->GetBinContent(i+1);
	}	
	
	TGraph *g200 = new TGraph(nbins,xvals,y200);
	TGraph *g62 = new TGraph(nbins,xvals,y62);
	TGraph *g39 = new TGraph(nbins,xvals,y39);
	TGraph *g20 = new TGraph(nbins,xvals,y20);
	TGraph *g7 = new TGraph(nbins,xvals,y7);

	g200->SetLineColor(kRed+1);
	g62->SetLineColor(kOrange+7);
	g39->SetLineColor(kSpring-1);
	g20->SetLineColor(kAzure-3);
	g7->SetLineColor(kViolet+1);

	hv2_pT[0]->SetFillColor(kRed+1);
	hv2_pT[1]->SetFillColor(kOrange+7);
	hv2_pT[2]->SetFillColor(kSpring-1);
	hv2_pT[3]->SetFillColor(kAzure-3);
	hv2_pT[4]->SetFillColor(kViolet+1);

	TCanvas *c2 = new TCanvas("c2","c2",700,700);
	hv2_pT[0]->Draw("E3");
	hv2_pT[1]->Draw("E3,same");
	hv2_pT[2]->Draw("E3,same");
	hv2_pT[3]->Draw("E3,same");
	hv2_pT[4]->Draw("E3,same");

	g200->Draw("L,same");
	g62->Draw("L,same");
	g39->Draw("L,same");
	g20->Draw("L,same");
	g7->Draw("L,same");
}

void plotPartonObservables()
{
	readFile();
	drawNscatt();
	drawv2();
}