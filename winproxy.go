package winproxy

/*
#cgo LDFLAGS: -lwininet
#include "c/proxy.c"
*/
import "C"

func SetProxy(enable bool) bool {
	if enable {
		return C.switch_system_proxy(1) == 1
	} else {
		return C.switch_system_proxy(0) == 1
	}
}

func SetServer(server string) bool {
	return C.set_system_proxy_server(C.CString(server)) == 1
}

// SetBypassList such as "localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;
func SetBypassList(bypass string) bool {
	return C.set_system_proxy_bypass_list(C.CString(bypass)) == 1
}
