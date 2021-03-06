// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Windows\\System32\\wmp.dll" no_namespace
// CWMPSettings2 包装器类

class CWMPSettings2 : public COleDispatchDriver
{
public:
	CWMPSettings2() {} // 调用 COleDispatchDriver 默认构造函数
	CWMPSettings2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPSettings2(const CWMPSettings2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IWMPSettings2 方法
public:
	BOOL get_isAvailable(LPCTSTR bstrItem)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, bstrItem);
		return result;
	}
	BOOL get_autoStart()
	{
		BOOL result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_autoStart(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_baseURL()
	{
		CString result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_baseURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_defaultFrame()
	{
		CString result;
		InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_defaultFrame(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_invokeURLs()
	{
		BOOL result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_invokeURLs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_mute()
	{
		BOOL result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_mute(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_playCount()
	{
		long result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_playCount(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_rate()
	{
		double result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_rate(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_balance()
	{
		long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_balance(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_volume()
	{
		long result;
		InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_volume(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL getMode(LPCTSTR bstrMode)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bstrMode);
		return result;
	}
	void setMode(LPCTSTR bstrMode, BOOL varfMode)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, bstrMode, varfMode);
	}
	BOOL get_enableErrorDialogs()
	{
		BOOL result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_enableErrorDialogs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_defaultAudioLanguage()
	{
		long result;
		InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	CString get_mediaAccessRights()
	{
		CString result;
		InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	BOOL requestMediaAccessRights(LPCTSTR bstrDesiredAccess)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bstrDesiredAccess);
		return result;
	}

	// IWMPSettings2 属性
public:

};
