#ifndef _DATA_H_
#define _DATA_H_

class DataHolder
{
public:
	const char* header;
	const char* item1;
	const char* item2;
	const char* item3;
	const char* footer;

	DataHolder(const char* _header, const char* _item1, const char* _item2, const char* _item3, const char* _footer)
		: header{_header}
		, item1{_item1}
		, item2{_item2}
		, item3{_item3}
		, footer{_footer}
	{ }
};

#endif
