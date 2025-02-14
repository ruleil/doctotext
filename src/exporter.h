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

#ifndef EXPORTER_H
#define EXPORTER_H

#include <algorithm>
#include <memory>

#include "chain_element.h"
#include "parser.h"
#include "parser_builder.h"
#include "parser_manager.h"
#include "parser_parameters.h"
#include "writer.h"
#include "defines.h"

namespace doctotext
{

class Importer;

/**
 *  @brief Exporter class is responsible for exporting the parsed data from importer or transformer to an output stream.
 *  @code
 *  Importer(parser_manager, "file.pdf") | PlainTextExporter() | std::cout; // Imports file.pdf and exports it to std::cout as plain text
 *  @endcode
 */
class DllExport Exporter : public ChainElement
{
public:
  /**
   * @param writer writer to use.
   */
  Exporter(std::unique_ptr<Writer> writer);

  /**
   * @param writer writer to use.
   * @param out_stream Exporter output stream. Exporter will be writing to this stream.
   */
  Exporter(std::unique_ptr<Writer> writer, std::ostream &out_stream);

  Exporter(const Exporter &other);

  Exporter(const Exporter &&other);

  virtual ~Exporter();

  bool is_leaf() const override
  {
    return true;
  }

  void process(doctotext::Info &info) const override;

  /**
   * @brief Sets output stream.
   * @param out_stream reference to output stream.
   */
  void set_out_stream(std::ostream &out_stream);

  /**
   * @brief Check if exporter contains valid output.
   * @brief True if output is valid.
   */
  bool is_valid() const;

  /**
   * @brief Exxports data from Info structure to output stream.
   * @param info data from callback function.
   */
  void export_to(doctotext::Info &info) const;

protected:
  std::ostream& get_output() const;

private:
  class Implementation;
  std::unique_ptr<Implementation> impl;
};

/**
 * @brief Exporter class for HTML output.
 */
class DllExport HtmlExporter: public Exporter
{
public:
  enum class RestoreOriginalAttributes : bool {};

  /**
   * @param restore_original_attributes should original html attributes extracted by html parser be restored
   */
  HtmlExporter(RestoreOriginalAttributes restore_original_attributes = RestoreOriginalAttributes{false});

  /**
   * @param out_stream Exporter output stream. Exporter will be writing to this stream.
   * @param restore_original_attributes should original html attributes extracted by html parser be restored
   */
  HtmlExporter(std::ostream &out_stream, RestoreOriginalAttributes restore_original_attributes = RestoreOriginalAttributes{false});

  HtmlExporter* clone() const override
  {
    return new HtmlExporter(*this);
  }
};

/**
 * @brief Exporter class for plain text output.
 */
class DllExport PlainTextExporter: public Exporter
{
public:
  PlainTextExporter();
  /**
   * @param out_stream Exporter output stream. Exporter will be writing to this stream.
   */
  PlainTextExporter(std::ostream &out_stream);

  /**
   * @param out_stream Exporter output stream. Exporter will be writing to this stream.
   */
  PlainTextExporter(std::ostream &&out_stream);

  PlainTextExporter* clone() const override
  {
    return new PlainTextExporter(*this);
  }

};

namespace experimental
{

/**
 * @brief Exporter class for CSV output.
 */
class DllExport CsvExporter: public Exporter
{
public:
  CsvExporter();
  /**
   * @param out_stream Exporter output stream. Exporter will be writing to this stream.
   */
  CsvExporter(std::ostream &out_stream);

  CsvExporter* clone() const override
  {
    return new CsvExporter(*this);
  }
};

} // namespace experimental

/**
 * @brief Exporter class for meta data.
 * Important: Exports only meta data as a plain text.
 */
class DllExport MetaDataExporter: public Exporter
{
public:
  MetaDataExporter();
  /**
   * @param out_stream Exporter output stream. Exporter will be writing to this stream.
   */
  MetaDataExporter(std::ostream &out_stream);

  MetaDataExporter* clone() const override
  {
    return new MetaDataExporter(*this);
  }


};

} // namespace doctotext

#endif //EXPORTER_H
