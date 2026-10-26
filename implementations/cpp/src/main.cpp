#include <harald/catalog.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace {
void usage() {
    std::cout << "HARALD C++ catalog prototype (SQLite, schema v1)\n"
              << "Usage: harald_cli --db FILE init|seed|list [term]|show EDITION_ID\n"
              << "       harald_cli --db FILE add-book TITLE CREATOR EDITION ISBN BARCODE1 LOCATION1 BARCODE2 LOCATION2\n"
              << "Commands: init creates/opens schema; seed inserts ONE sample book only into an empty DB.\n";
}
void printSummary(const harald::BookSummary& x) {
    std::cout << "Edition " << x.edition_id << " | " << x.title << " | " << x.creator
              << " | " << x.edition_label << " | ISBN " << x.isbn
              << " | copies: " << x.copy_count << '\n';
}
} // namespace

int main(int argc, char** argv) {
    try {
        if (argc < 4 || std::string(argv[1]) != "--db") {
            usage();
            return EXIT_FAILURE;
        }
        const std::string db_path(argv[2]);
        const std::string command(argv[3]);
        harald::SqliteCatalog repository(db_path);
        harald::CatalogService service(repository);
        if (command == "init" && argc == 4) {
            std::cout << "Catalog ready: " << db_path << '\n';
        } else if (command == "seed" && argc == 4) {
            if (!service.search("").empty()) {
                std::cout << "Catalog is not empty: sample data not inserted.\n";
                return EXIT_FAILURE;
            }
            const harald::Id id = service.createBook({
                "The Example Library", "HARALD Sample Author", "First edition", "",
                {{"HAR-0001", "Library / Shelf A"}, {"HAR-0002", "Office / Shelf B"}}
            });
            std::cout << "Created sample edition " << id << " with two copies.\n";
        } else if (command == "list" && (argc == 4 || argc == 5)) {
            const std::string term = argc == 5 ? argv[4] : "";
            const auto books = service.search(term);
            for (const auto& book : books) printSummary(book);
            std::cout << books.size() << " edition(s)\n";
        } else if (command == "show" && argc == 5) {
            const std::string id_text(argv[4]);
            std::size_t parsed = 0;
            const harald::Id id = std::stoll(id_text, &parsed);
            if (parsed != id_text.size()) throw std::invalid_argument("invalid edition ID");
            auto book = service.details(id);
            if (!book) {
                std::cerr << "Edition not found\n";
                return EXIT_FAILURE;
            }
            printSummary(book->book);
            for (const auto& item : book->copies) {
                std::cout << "  Copy " << item.id << " | " << item.inventory_code
                          << " | " << item.location << '\n';
            }
        } else if (command == "add-book" && argc == 12) {
            const harald::Id id = service.createBook({argv[4], argv[5], argv[6], argv[7],
                {{argv[8], argv[9]}, {argv[10], argv[11]}}});
            std::cout << "Created edition " << id << " with two copies.\n";
        } else {
            usage();
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "HARALD error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
