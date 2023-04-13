class MarkupDocument {
    char *header;
    char *body;
    char *footer;
};

class IMarkupLexer {};

class IMarkupSentinel {}; // Destroy values with the 'Sentinel'

class IDocumentHandler {
    MarkupDocument retrieve_document_function(IDocumentHandler *handle);
    MarkupDocument initialize_marked_function(IDocumentHandler *handle);

public:
    MarkupDocument retrieve_document(IDocumentHandler *handle) {
        return handle->retrieve_document_function(handle);
    }

    MarkupDocument initialize_markup_document(MarkupDocument *document)  {
        return *document;
    }
};

class IDocumentServiceAnnul {
    void nullify_service_function(IDocumentServiceAnnul*); // Do absolutely nothing...nada...

public:
    void nullify_service(IDocumentServiceAnnul*) {} // Does nothing...it's just void...what!?
};