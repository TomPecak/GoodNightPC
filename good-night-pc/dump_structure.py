import os

# ================= KONFIGURACJA =================
# Katalog, od którego zaczynamy skanowanie (względem miejsca, gdzie jest ten skrypt)
# "." oznacza bieżący katalog
# ".." oznacza katalog nadrzędny
# "nazwa_folderu" oznacza podfolder
KATALOG_STARTOWY = "." 

# Nazwa pliku wynikowego
PLIK_WYNIKOWY = "dump_proj_structure.txt"

# Lista folderów i plików do pominięcia (żeby nie zaśmiecać wyniku)
IGNOROWANE = {}
# ================================================

def generuj_drzewo(katalog, prefix=""):
    """
    Rekurencyjna funkcja do budowania struktury drzewa.
    """
    struktura = ""
    
    try:
        # Pobieramy listę plików i sortujemy alfabetycznie dla porządku
        elementy = sorted(os.listdir(katalog))
    except PermissionError:
        return f"{prefix}[Brak dostępu do katalogu]\n"
    except FileNotFoundError:
        return f"{prefix}[Katalog nie istnieje: {katalog}]\n"

    # Filtrujemy elementy, które są na liście ignorowanych
    elementy = [e for e in elementy if e not in IGNOROWANE]
    
    # Iterujemy przez elementy
    for i, element in enumerate(elementy):
        sciezka = os.path.join(katalog, element)
        czy_ostatni = (i == len(elementy) - 1)
        
        # Ustawiamy odpowiedni znak graficzny (gałąź lub koniec gałęzi)
        znacznik = "└── " if czy_ostatni else "├── "
        
        struktura += f"{prefix}{znacznik}{element}\n"
        
        # Jeśli to katalog, wchodzimy głębiej (rekurencja)
        if os.path.isdir(sciezka):
            nowy_prefix = prefix + ("    " if czy_ostatni else "│   ")
            struktura += generuj_drzewo(sciezka, nowy_prefix)
            
    return struktura

def main():
    # Ustalanie pełnej ścieżki startowej
    sciezka_bazowa = os.path.abspath(KATALOG_STARTOWY)
    
    print(f"Generowanie struktury dla: {sciezka_bazowa}...")
    
    # Nagłówek w pliku
    tresc = f"Zrzut struktury katalogu: {sciezka_bazowa}\n"
    tresc += "=" * 50 + "\n"
    tresc += f".\n" # Oznaczenie korzenia
    
    # Generowanie treści
    tresc += generuj_drzewo(sciezka_bazowa)
    
    # Zapis do pliku
    try:
        with open(PLIK_WYNIKOWY, "w", encoding="utf-8") as f:
            f.write(tresc)
        print(f"Sukces! Struktura zapisana w pliku: {PLIK_WYNIKOWY}")
    except Exception as e:
        print(f"Błąd podczas zapisu pliku: {e}")

if __name__ == "__main__":
    main()