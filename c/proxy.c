#include <windows.h>
#include <wininet.h>
#include <stdio.h>

BOOL switch_system_proxy(BOOL enable)
{
    INTERNET_PER_CONN_OPTION_LIST list;
    BOOL bReturn;
    DWORD dwBufSize = sizeof(list);
    // fill put list struct
    list.dwSize = sizeof(list);
    // nullptr == LAN, otherwise connectoid name.
    list.pszConnection = NULL;
    // set three options
    list.dwOptionCount = 1;
    INTERNET_PER_CONN_OPTION options[list.dwOptionCount];
    list.pOptions = options;

    // Make sure the memeory wa allocated
    if (NULL == list.pOptions)
    {
        printf("failed to allocate memory for options\n");
        return FALSE;
    }

    // set flags
    list.pOptions[0].dwOption = INTERNET_PER_CONN_FLAGS;
    if (enable)
    {
        printf("enable proxy, set INTERNET_PER_CONN_FLAGS to PROXY_TYPE_DIRECT | PROXY_TYPE_PROXY\n");
        list.pOptions[0].Value.dwValue = PROXY_TYPE_DIRECT | PROXY_TYPE_PROXY;
    }
    else
    {
        printf("disenabled proxy, set INTERNET_PER_CONN_FLAGS to PROXY_TYPE_DIRECT\n");
        list.pOptions[0].Value.dwValue = PROXY_TYPE_DIRECT;
    }
    // Set the options on the connection.
    bReturn = InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &list, dwBufSize);
    InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
    return bReturn;
}

BOOL set_system_proxy_server(char *proxy_full_addr)
{
    INTERNET_PER_CONN_OPTION_LIST list;
    BOOL bReturn;
    DWORD dwBufSize = sizeof(list);
    // fill put list struct
    list.dwSize = sizeof(list);
    // nullptr == LAN, otherwise connectoid name.
    list.pszConnection = NULL;
    // set three options
    list.dwOptionCount = 1;
    INTERNET_PER_CONN_OPTION options[list.dwOptionCount];
    list.pOptions = options;

    // Make sure the memeory wa allocated
    if (NULL == list.pOptions)
    {
        printf("failed to allocate memory for options\n");
        return FALSE;
    }

    printf("set proxy server to %s\n", proxy_full_addr);

    // set flags
    list.pOptions[0].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    list.pOptions[0].Value.pszValue = proxy_full_addr;
    // Set the options on the connection.
    bReturn = InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &list, dwBufSize);
    // delete[] list.pOptions;
    InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
    return bReturn;
}

// localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;172.20.*;172.21.*;172.22.*;172.23.*;172.24.*;172.25.*;172.26.*;172.27.*;172.28.*;172.29.*;172.30.*;172.31.*;172.32.*;192.168.*
BOOL set_system_proxy_bypass_list(char *bypass)
{
    INTERNET_PER_CONN_OPTION_LIST list;
    BOOL bReturn;
    DWORD dwBufSize = sizeof(list);
    // fill put list struct
    list.dwSize = sizeof(list);
    // nullptr == LAN, otherwise connectoid name.
    list.pszConnection = NULL;
    // set three options
    list.dwOptionCount = 1;
    INTERNET_PER_CONN_OPTION options[list.dwOptionCount];
    list.pOptions = options;

    // Make sure the memeory wa allocated
    if (NULL == list.pOptions)
    {
        printf("failed to allocate memory for options\n");
        return FALSE;
    }

    printf("set proxy bypass list to %s\n", bypass);

    // set flags
    list.pOptions[0].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
    list.pOptions[0].Value.pszValue = bypass;
    // Set the options on the connection.
    bReturn = InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &list, dwBufSize);
    // delete[] list.pOptions;
    InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
    return bReturn;
}