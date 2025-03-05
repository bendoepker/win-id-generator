#include <iostream>

#include <windows.h>
#include <mmdeviceapi.h>

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

static void exitOnError(HRESULT hres) {
    if(hres != S_OK) { printf("Error: %ld\n", hres); exit(0); }
};

static wchar_t* id_to_guid(LPOLESTR in) {

    /*
        * Reference 'in' : {BCDE0395-E52F-467C-8E3D-C4579291692E}
        *                   1------- 10-- 15-- 20-- 25  29  33
        *                                             27  31  35
        * 
        * Reference 'out' : {0xBCDE0395, 0xE52F, 0x467C, {0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E}}
        *                   0  3-------11  15--19  23--27   32    38    44    50    56    62    68    74
        *                                                 30  34    40    46    52    58    64    70    76
    */

    wchar_t curChar;
    wchar_t out[79];
    out[0] = (wchar_t)'{';
    out[1] = (wchar_t)'0';
    out[2] = (wchar_t)'x';

    //First long
    for (int i = 0; i < 8; i++) {
        out[i + 3] = in[i + 1];
    }

    out[11] = (wchar_t)',';
    out[12] = (wchar_t)' ';
    out[13] = (wchar_t)'0';
    out[14] = (wchar_t)'x';

    //First short
    for (int i = 0; i < 4; i++) {
        out[i + 15] = in[i + 10];
    }

    out[19] = (wchar_t)',';
    out[20] = (wchar_t)' ';
    out[21] = (wchar_t)'0';
    out[22] = (wchar_t)'x';

    //Second short
    for (int i = 0; i < 4; i++) {
        out[i + 23] = in[i + 15];
    }

    out[27] = (wchar_t)',';
    out[28] = (wchar_t)' ';
    out[29] = (wchar_t)'{';

    //First char sequence
    out[30] = (wchar_t)'0';
    out[31] = (wchar_t)'x';
    out[32] = in[20];
    out[33] = in[21];
    out[34] = (wchar_t)',';
    out[35] = (wchar_t)' ';


    //Second char sequence
    out[36] = (wchar_t)'0';
    out[37] = (wchar_t)'x';
    out[38] = in[22];
    out[39] = in[23];
    out[40] = (wchar_t)',';
    out[41] = (wchar_t)' ';

    //Char 3-8 sequence
    for (int i = 0; i < 6; i++) {
        out[42 + (6 * i)] = (wchar_t)'0';
        out[43 + (6 * i)] = (wchar_t)'x';
        out[44 + (6 * i)] = in[25 + (2 * i)];
        out[45 + (6 * i)] = in[26 + (2 * i)];
        if(i != 5) out[46 + (6 * i)] = (wchar_t)',';
        if(i != 5) out[47 + (6 * i)] = (wchar_t)' ';
    }

    out[76] = (wchar_t)'}';
    out[77] = (wchar_t)'}';
    out[78] = '\0';

    return out;
}

void printID() {
    LPOLESTR str;
    HRESULT hres = StringFromCLSID(CLSID_MMDeviceEnumerator, &str);
    exitOnError(hres);
    printf("CLSID_MMDeviceEnumerator: %ls\n", id_to_guid(str));

    //Copy / Paste the formula below with the desired GUID / CLSID / IID / etc.
    hres = StringFromCLSID(IID_IMMDeviceEnumerator, &str);
    exitOnError(hres);
    printf("IID_IMMDeviceEnumerator: %ls\n", id_to_guid(str));
}

int main() {
    printID();
}
