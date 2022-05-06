package winproxy

/*
#cgo LDFLAGS: -lwininet
#include "c/proxy.c"
*/
import "C"
import "unsafe"

func SetProxy(enable bool) bool {
	if enable {
		return C.switch_system_proxy(1) == 1
	} else {
		return C.switch_system_proxy(0) == 1
	}
}

func SetServer(server string) bool {
	s := C.CString(server)
	defer C.free(unsafe.Pointer(s))
	return C.set_system_proxy_server(s) == 1
}

// SetBypassList such as "localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;
func SetBypassList(bypass string) bool {
	s := C.CString(bypass)
	defer C.free(unsafe.Pointer(s))
	return C.set_system_proxy_bypass_list(s) == 1
}
