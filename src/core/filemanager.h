#ifndef FILEMANAGER_H
#define FILEMANAGER_H
 
#include <string>
#include <fstream>
#include <stdexcept>
#include "university.h"
 
class FileManager {
private:
    std::string filename;
 
    // ── Private helpers for writing ──────────────────────────
    void saveStudent   (std::ofstream& out, const Student&    s) const;
    void saveDormitory (std::ofstream& out, const Dormitory&  d) const;
    void saveRoom      (std::ofstream& out, const Room&       r) const;
    void saveRestaurant(std::ofstream& out, const Restaurant& r) const;
    void saveMenu      (std::ofstream& out, const Menu&       m) const;
 
    // ── Private helpers for reading ──────────────────────────
    Student    loadStudent   (std::ifstream& in) const;
    Dormitory  loadDormitory (std::ifstream& in) const;
    Room       loadRoom      (std::ifstream& in) const;
    Restaurant loadRestaurant(std::ifstream& in) const;
    Menu       loadMenu      (std::ifstream& in) const;
 
public:
    // Constructor
    FileManager(const std::string& filename);
 
    // ── Public interface ─────────────────────────────────────
    void      saveUniversity(const University& university) const;
    University loadUniversity()                            const;
};
 
#endif
 