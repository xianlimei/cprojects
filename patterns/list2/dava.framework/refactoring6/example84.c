if ((node->type != XML_ELEMENT_NODE) &&
		    (node->type != XML_DOCUMENT_NODE) &&
#ifdef LIBXML_DOCB_ENABLED
		    (node->type != XML_DOCB_DOCUMENT_NODE) &&
#endif
		    (node->type != XML_HTML_DOCUMENT_NODE))
		    goto rollback;
