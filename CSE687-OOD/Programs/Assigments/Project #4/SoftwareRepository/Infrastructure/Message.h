#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include "XmlDoc.h"

namespace Ider
{


	struct MsgType
	{
		enum Value
		{
			Login,
			Dependency,
			File,
			Checkin,
			Warning,

			Unknown
		};
		static strVal EnumToString(MsgType::Value type);
		static Value StringToEnum(conStrRef type);
	};

	class Message
	{
	public:
		Message(){ type = MsgType::Unknown;}
		Message(conStrRef xml);

		MsgType::Value Type()const{return type;}
		XmlDoc Doc()const{return doc;}
		virtual void SetMessage(conStrRef xml);
		strVal ToString()const{return doc.ToString();}
	protected:
		virtual	void  SetType(strVal tagName);

	private:
		XmlDoc doc;
		MsgType::Value type;

	};
}

#endif