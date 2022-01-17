#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <Strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <dir.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>
#include <Lmcons.h>
#include <ctime>
#include <winver.h>

using namespace std;

string productName = "PhoneFraud Pursuit";
string productNaFo = "PhoneFraudPursuit";
string productDesc = "Automated Scammer Number Finder";
string productVers = "1.1.5";
string productAuth = "Leo Takacs // Scam Baiting";
string productAuthShort = "Leo Takacs";
string fileStampStr = "===== These numbers were found by " + productName + " v" + productVers + " =====\n\t\tby " + productAuth;
string websiteURL = "http://leotakacs.com";
string youtubeURL = "http://YouTube.com/c/LeoTakacs";
string filename;

char const * DownloadKeywords[] = {
  "keyword:printersupport",
  "keyword:canonprintersupport",
  "keyword:printersupportnumber",
  "keyword:canonprintersupportnumber",
  "keyword:tech support",
  "keyword:windowssupportnumber",
  "keyword:techsupport",
  "keyword:techsupportnumber",
  "keyword:windows support number"
};
char badchars[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*_+=~{}|:\"\'<>?/,";
char badcharsStage2[] = "()-";
char cmd[1024];
char fileStamp[1024];
char openTxtCmd[1024];
char searchdata[1024];
char wintitle[300];

bool codeFlag;

string readstring;

vector <string> files;
vector <string> searchcodes = {
  "800",
  "806",
  "808",
  "833",
  "844",
  "855",
  "865",
  "877",
  "888"
};

string parseNumber(int number) {
  cout << number << endl;
}

string returnDateTimeStamp(){
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];
  time (&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer,sizeof(buffer),"%m-%d-%Y_%H-%M-%S",timeinfo);
  std::string str(buffer);
  return str;
}

int main() {
  sprintf(fileStamp, "%s", fileStampStr.c_str());
  sprintf(wintitle, "\t\t\t\t\t%s v%s\n\t\t\t\t\t by %s", productName.c_str(), productVers.c_str(), productAuth.c_str());
  SetConsoleTitle(wintitle);
  ifstream testPath("WebHelper.dll");
  if (testPath.fail()){
    cout << "An important file is missing!\nLeo's Scammer Number Locator will now close." << endl;
    system("pause > nul");
    return 1;
  }
  system("echo #DFG_FLAG=1 > helperinfo");
  cout << endl << "=======================================================================================================================" << endl;
  cout << wintitle << endl;
  cout << "\t\t" << websiteURL << "\t\t\t\t\t\t" << youtubeURL << endl;
  cout << "=======================================================================================================================\n" << endl;
  cout << "[*] Press any button to instantly find scammer numbers!" << endl;
  system("pause > nul");
  cout << "[*] Searching the entire internet for scammer numbers....." << endl;
  sprintf(searchdata, "%s\\searchdata", getenv("USERPROFILE"));
  remove(searchdata);
  for (int i = 0; i < sizeof(DownloadKeywords) / sizeof(DownloadKeywords[0]); i++) {
    sprintf(cmd, "WebHelper.dll -cfg=helperinfo http://www.google.com/search?q=%s --dump >> %%userprofile%%\\searchdata", DownloadKeywords[i], i);
    system(cmd);
  }
  system("del /f /q helperinfo");
  filename = "_" + productNaFo + "_"+returnDateTimeStamp()+".results.txt";
  ifstream infile(searchdata);
  ofstream outfile(filename);
  outfile << fileStampStr + "\n\n\n\n";
  while (getline(infile, readstring)) {
    if (readstring.find("8") != string::npos && readstring.find("]") != string::npos) {
      for (int i = 0; i < strlen(badchars); i++) {
        readstring.erase(std::remove(readstring.begin(), readstring.end(), badchars[i]), readstring.end());
      }
      readstring = readstring.substr(readstring.find("]") + 1);
      for (int i = 0; i < strlen(badcharsStage2); i++) {
        readstring.erase(std::remove(readstring.begin(), readstring.end(), badcharsStage2[i]), readstring.end());
      }
      codeFlag = false;
      for (int i = 0; i < searchcodes.size(); i++) {
        if (readstring.find(searchcodes[i]) != string::npos) {
          codeFlag = true;
        }
      }
      if (codeFlag) {
        if (readstring.size() > 5) {
          readstring = readstring.substr(0, 11).insert(1, "-").insert(2, "(").insert(6, ")").insert(7, "-").insert(11, "-");
          if (readstring.find("(0") == string::npos && readstring.find("(1") == string::npos && readstring.find("8-(") == string::npos) {
              outfile << readstring + "\n";
          }
        }
      }
    }
  }
  outfile << "\n\n\n";
  outfile << fileStampStr;
  outfile << "\n\n";
  outfile << websiteURL.c_str() << "\n" << youtubeURL.c_str();
  cout << "[*] Done!\n[*] Now opening " + filename + ".....";
  infile.close();
  outfile.close();
  remove(searchdata);
  sprintf(openTxtCmd, "start notepad %s", filename.c_str());
  system(openTxtCmd);
  Sleep(5000);
  return 0;
}
