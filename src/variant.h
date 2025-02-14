/***************************************************************************************************************************************************/
/*  DocToText - A multifaceted, data extraction software development toolkit that converts all sorts of files to plain text and html.              */
/*  Written in C++, this data extraction tool has a parser able to convert PST & OST files along with a brand new API for better file processing.  */
/*  To enhance its utility, DocToText, as a data extraction tool, can be integrated with other data mining and data analytics applications.        */
/*  It comes equipped with a high grade, scriptable and trainable OCR that has LSTM neural networks based character recognition.                   */
/*                                                                                                                                                 */
/*  This document parser is able to extract metadata along with annotations and supports a list of formats that include:                           */
/*  DOC, XLS, XLSB, PPT, RTF, ODF (ODT, ODS, ODP), OOXML (DOCX, XLSX, PPTX), iWork (PAGES, NUMBERS, KEYNOTE), ODFXML (FODP, FODS, FODT),           */
/*  PDF, EML, HTML, Outlook (PST, OST), Image (JPG, JPEG, JFIF, BMP, PNM, PNG, TIFF, WEBP), Archives (ZIP, TAR, RAR, GZ, BZ2, XZ)                  */
/*  and DICOM (DCM)                                                                                                                                */
/*                                                                                                                                                 */
/*  Copyright (c) SILVERCODERS Ltd                                                                                                                 */
/*  http://silvercoders.com                                                                                                                        */
/*                                                                                                                                                 */
/*  Project homepage:                                                                                                                              */
/*  http://silvercoders.com/en/products/doctotext                                                                                                  */
/*  https://www.docwire.io/                                                                                                                        */
/*                                                                                                                                                 */
/*  The GNU General Public License version 2 as published by the Free Software Foundation and found in the file COPYING.GPL permits                */
/*  the distribution and/or modification of this application.                                                                                      */
/*                                                                                                                                                 */
/*  Please keep in mind that any attempt to circumvent the terms of the GNU General Public License by employing wrappers, pipelines,               */
/*  client/server protocols, etc. is illegal. You must purchase a commercial license if your program, which is distributed under a license         */
/*  other than the GNU General Public License version 2, directly or indirectly calls any portion of this code.                                    */
/*  Simply stop using the product if you disagree with this viewpoint.                                                                             */
/*                                                                                                                                                 */
/*  According to the terms of the license provided by SILVERCODERS and included in the file COPYING.COM, licensees in possession of                */
/*  a current commercial license for this product may use this file.                                                                               */
/*                                                                                                                                                 */
/*  This program is provided WITHOUT ANY WARRANTY, not even the implicit warranty of merchantability or fitness for a particular purpose.          */
/*  It is supplied in the hope that it will be useful.                                                                                             */
/***************************************************************************************************************************************************/

#ifndef DOCTOTEXT_VARIANT_H
#define DOCTOTEXT_VARIANT_H

#include <string>
#include <time.h>
#include "defines.h"

namespace doctotext
{
	/**
		Variant is an object which can represent unsigned number, date or string.
		Uninitialized object represents 'null'.
	**/
	class DllExport Variant
	{
		private:
			struct Implementation;
			Implementation* impl;

		public:

			///Creates uninitialized object (represents null)
			Variant();

			///Creates object which represents string
			Variant(const std::string& value);

			///Creates object which represents date
			Variant(const tm& value);

			///Creates object which represents unsigned number
			Variant(size_t value);

			///Creates a copy of another Variant
			Variant(const Variant& variant);
			~Variant();
			Variant& operator = (const Variant& variant);

			///Sets unsigned number value. From this moment, Variant represents unsigned number.
			void setValue(size_t number);

			///Sets date value. From this moment, Variant represents date.
			void setValue(const tm& date_time);

			///Sets string value. From this moment, Variant represents string.
			void setValue(const std::string& str);

			///If Variant has not been initialized with number/date/string, this method returns value true
			bool isEmpty() const;

			///Checks if Variant represents a string
			bool isString() const;

			///Checks if Variant represents a number
			bool isNumber() const;

			///Checks if Variant represents a date
			bool isDateTime() const;

			/**
				If Variant is a date, this method returns const reference to tm object. But if it is not
				a date, struct tm can be filled with undefined numbers (usually zeros)
			**/
			const tm& getDateTime() const;

			/**
				Returns string value. If Variant is a string, then string is returned (simple). But if variant represents
				number or a date, proper value is converted to the string. If variant has no value (represents null),
				empty string is returned.
			**/
			const char* getString() const;

			/**
				If Variant is a number, then number which is inside this object is returned. In other cases,
				returned number may be undefined (usually 0).
			**/
			size_t getNumber() const;
	};
} // namespace doctotext

#endif
