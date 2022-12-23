#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{
    const int DATA_AMOUNT = 2;
    const char* privatURL = "https://api.privatbank.ua/p24api/pubinfo?json&exchange&coursid=5";
    const char* bankgovuaURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
    const char* destFilePrivat = "privat.txt";
    const char* destFileBankGovUa = "BankGovUa.txt";
    string prepaPrivatBank, postparcingPrivat, prepaBankUa, postparcingGovBankUa, buffer;
    string subject_to_search[2]{ "EUR", "USD" };
    string subject_to_search2[2]{ "\"cc\":\"EUR\"", "\"cc\":\"USD\"" };

    if (S_OK != URLDownloadToFileA(NULL, privatURL, destFilePrivat, 0, NULL))
    {
        cout << "Error ";
    }
    if (S_OK != URLDownloadToFileA(NULL, bankgovuaURL, destFileBankGovUa, 0, NULL))
    {
        cout << "Error ";
    }

    ifstream ingov("BankGovUa.txt");
    if (ingov.is_open())
    {
        while (getline(ingov, buffer))
        {
            prepaBankUa += buffer;
        }
    }
    ingov.close();

    ifstream in("privat.txt");
    if (in.is_open())
    {
        while (getline(in, buffer))
        {
            prepaPrivatBank += buffer;
        }
    }
    in.close();
    cout << endl;

    for (int i = 0; i < DATA_AMOUNT; i++)
    {
        size_t found = prepaPrivatBank.find(subject_to_search[i]);
        postparcingPrivat += subject_to_search[i] + " - ";
        for (int j = found + 29; prepaPrivatBank[j] != '"'; j++)
        {
            if (prepaPrivatBank[j] != '"') {
                postparcingPrivat += prepaPrivatBank[j];
            }
        }
        postparcingPrivat += ' ';
    }

    for (int i = 0; i < DATA_AMOUNT; i++)
    {
        size_t found = prepaBankUa.find(subject_to_search2[i]);
        postparcingGovBankUa += subject_to_search[i] + " - ";
        for (int j = found - 7; prepaBankUa[j] != ','; j++)
        {
            if (prepaBankUa[j] != ',') {
                postparcingGovBankUa += prepaBankUa[j];
            }
        }
        postparcingGovBankUa += ' ';
    }
    cout << "Privat Bank: " << postparcingPrivat << endl;
    cout << "Bank Gov Ua: " << postparcingGovBankUa << endl;
   
    return 0;
}