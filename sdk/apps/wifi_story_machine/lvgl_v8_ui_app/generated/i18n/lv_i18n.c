#include "./lv_i18n.h"

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val)
{
    return (uint32_t)(val < 0 ? -val : val);
}
static inline uint32_t op_i(uint32_t val)
{
    return val;
}
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val)
{
    UNUSED(val);
    return 0;
}
static inline uint32_t op_w(uint32_t val)
{
    UNUSED(val);
    return 0;
}
static inline uint32_t op_f(uint32_t val)
{
    UNUSED(val);
    return 0;
}
static inline uint32_t op_t(uint32_t val)
{
    UNUSED(val);
    return 0;
}

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {

    NULL // End mark
};
////////////////////////////////////////////////////////////////////////////////

// Internal state
static const lv_i18n_language_pack_t *current_lang_pack;
static const lv_i18n_lang_t *current_lang;


/**
* Reset internal state. For testing.
*/
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
* Set the languages for internationalization
* @param langs pointer to the array of languages. (Last element has to be `NULL`)
*/
int lv_i18n_init(const lv_i18n_language_pack_t *langs)
{
    if (langs == NULL) {
        return -1;
    }
    if (langs[0] == NULL) {
        return -1;
    }

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
* Change the localization (language)
* @param l_name name of the translation locale to use. E.g. "en-GB"
*/
int lv_i18n_set_locale(const char *l_name)
{
    if (current_lang_pack == NULL) {
        return -1;
    }

    uint16_t i;

    for (i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if (strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char *__lv_i18n_get_text_core(lv_i18n_phrase_t *trans, const char *msg_id)
{
    uint16_t i;
    for (i = 0; trans[i].msg_id != NULL; i++) {
        if (strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if (trans[i].translation) {
                return trans[i].translation;
            }
        }
    }

    return NULL;
}


/**
* Get the translation from a message ID
* @param msg_id message ID
* @return the translation of `msg_id` on the set local
*/
const char *lv_i18n_get_text(const char *msg_id)
{
    if (current_lang == NULL) {
        return msg_id;
    }

    const lv_i18n_lang_t *lang = current_lang;
    const void *txt;

    // Search in current locale
    if (lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) {
            return txt;
        }
    }

    // Try to fallback
    if (lang == current_lang_pack[0]) {
        return msg_id;
    }
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if (lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) {
            return txt;
        }
    }

    return msg_id;
}

/**
* Get the translation from a message ID and apply the language's plural rule to get correct form
* @param msg_id message ID
* @param num an integer to select the correct plural form
* @return the translation of `msg_id` on the set local
*/
const char *lv_i18n_get_text_plural(const char *msg_id, int32_t num)
{
    if (current_lang == NULL) {
        return msg_id;
    }

    const lv_i18n_lang_t *lang = current_lang;
    const void *txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if (lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if (lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) {
                return txt;
            }
        }
    }

    // Try to fallback
    if (lang == current_lang_pack[0]) {
        return msg_id;
    }
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if (lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if (lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) {
                return txt;
            }
        }
    }

    return msg_id;
}

typedef struct {
    const char *font_name;
    const lv_font_t *font_ptr;
} font_mapping_t;

static const font_mapping_t font_mapping[] = {

    {NULL, NULL} // End mark
};

const lv_font_t *lv_i18n_get_font_by_name(const char *font_name)
{
    if (font_name == NULL) {
        return NULL;
    }

    for (uint16_t i = 0; font_mapping[i].font_name != NULL; i++) {
        if (strcmp(font_mapping[i].font_name, font_name) == 0) {
            return font_mapping[i].font_ptr;
        }
    }

    return NULL;
}

/*
* Get the font for a message ID
* @param msg_id message ID
*/
const lv_font_t *lv_i18n_get_font(const char *msg_id)
{
    if (current_lang == NULL) {
        return NULL;
    }

    const lv_i18n_lang_t *lang = current_lang;
    const lv_font_t *font = NULL;

    // Search in current locale singulars
    if (lang->singulars != NULL) {
        for (uint16_t i = 0; lang->singulars[i].msg_id != NULL; i++) {
            if (strcmp(lang->singulars[i].msg_id, msg_id) == 0) {
                const char *font_name = lang->singulars[i].font_name;
                font = lv_i18n_get_font_by_name(font_name);
                return font;
            }
        }
    }

    // Search in current locale plurals for type ONE
    if (lang->plurals[LV_I18N_PLURAL_TYPE_ONE] != NULL) {
        for (uint16_t i = 0; lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].msg_id != NULL; i++) {
            if (strcmp(lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].msg_id, msg_id) == 0) {
                const char *font_name = lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].font_name;
                font = lv_i18n_get_font_by_name(font_name);
                return font;
            }
        }
    }

    // Search in current locale plurals for type OTHER
    if (lang->plurals[LV_I18N_PLURAL_TYPE_OTHER] != NULL) {
        for (uint16_t i = 0; lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].msg_id != NULL; i++) {
            if (strcmp(lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].msg_id, msg_id) == 0) {
                const char *font_name = lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].font_name;
                font = lv_i18n_get_font_by_name(font_name);
                return font;
            }
        }
    }

    return NULL;
}

/**
* Get the name of the currently used locale.
* @return name of the currently used locale. E.g. "en-GB"
*/
const char *lv_i18n_get_current_locale(void)
{
    if (!current_lang) {
        return NULL;
    }
    return current_lang->locale_name;
}