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

#ifndef DOCTOTEXT_ATTACHMENT_H
#define DOCTOTEXT_ATTACHMENT_H

#include <map>
#include <string>
#include "variant.h"
#include "defines.h"

namespace doctotext
{
	/**
		Structure of the attachment in parsed file.
		If parsed file has an attachments, PlainTextExtractor will try to get them.
		Attachment is usually another file. Another thing worth mentioning is that attachments may hold
		metadada.
	**/
	class DllExport Attachment
	{
		private:
			struct Implementation;
			Implementation* impl;

		public:
			Attachment();
			Attachment(const std::string& file_name);
			Attachment(const Attachment& attachment);
			Attachment& operator = (const Attachment& attachment);
			~Attachment();
			void setFileName(const std::string& file_name);
			void setBinaryContent(const std::string& binary_content);
			void addField(const std::string& field_name, const Variant& field_value);

			///Gets attachment file name
			const char* filename() const;

			///Gets binary content of the attachment
			const char* binaryContent() const;

			///Returns size of the binary content
			size_t binaryContentSize() const;

			///Checks if metadata for given key exist (for example "Content-Type")
			bool hasField(const std::string& field_name) const;

			///Returns value for given key (metadata)
			const Variant& getField(const std::string& field_name) const;

			///Returns map with all keys and values
			const std::map<std::string, Variant>& getFields() const;
	};
} // namespace doctotext

#endif
