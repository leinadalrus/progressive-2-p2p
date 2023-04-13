const std = @import("std");

const MarkupDocument = struct {
    header: []u8,
    body: []u8,
    footer: []u8,
};

const IDocumentHandler = struct {
    retrieve_document_function: fn (*IDocumentHandler) MarkupDocument,
    initialize_marked_model: fn (*MarkupDocument) MarkupDocument,

    fn retrieve_document_feedback(function: *IDocumentHandler) MarkupDocument {
        return function.retrieve_document_function(function);
    }

    fn initialize_markup_document(document: *MarkupDocument) MarkupDocument {
        return document;
    }
};

const IMarkupLexer = struct {};

const IMarkupDeferal = struct {}; // Destroy values with the 'Sentinel'

const IDocumentServiceAnnul = struct {
    nullify_service_function: fn (*IDocumentServiceAnnul) void, // Do absolutely nothing...nada...

    fn nullify_service() void {} // Does nothing...it's just void...what!?
};
