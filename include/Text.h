#ifndef TEXT
#define TEXT

#include <string>
#include <memory>
#include "Component.h"
#include "GameObject.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

class Text : public Component {
public: 
    enum TextStyle {SOLID, SHADED, BLENDED};
    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    ~Text();
    void Update(int dt);
    void Render();
    bool Is(const std::string& type);
    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
private:
    void RemakeTexture();
    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
};

#endif