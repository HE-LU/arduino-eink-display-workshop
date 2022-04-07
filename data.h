#ifndef _DATA_H_
#define _DATA_H_

class DataHolder
{
public:
	String header;
	String item1;
	String item2;
	String item3;
	String footer;

	DataHolder(String _header, String _item1, String _item2, String _item3, String _footer)
		: header{_header}
		, item1{_item1}
		, item2{_item2}
		, item3{_item3}
		, footer{_footer}
	{ }
};

#endif
