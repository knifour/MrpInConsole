namespace utf8{
	int getCodeLength(uint8_t);
	int isUtf8(const std::string& str);
	int isUtf8(const uint8_t* str);
	bool countChars(const std::string& str, int&);
	bool countChars(const uint8_t* str, int&);
}