import os
Import("env")

def patch_lv_conf(*args, **kwargs):
    print("Patching lv_conf.h to allow LV_FONT_FMT_TXT_LARGE override...")
    lv_conf_path = os.path.join(env.get("PROJECT_LIBDEPS_DIR"), env.get("PIOENV"), "LilyGo-AMOLED-Series", "src", "lv_conf.h")
    
    if os.path.exists(lv_conf_path):
        with open(lv_conf_path, "r", encoding="utf-8") as f:
            content = f.read()
        
        # We also check for 0 or 1 in case it was already modified to 1 manually
        if "#define LV_FONT_FMT_TXT_LARGE 0" in content:
            content = content.replace("#define LV_FONT_FMT_TXT_LARGE 0", 
                                      "#ifndef LV_FONT_FMT_TXT_LARGE\n#define LV_FONT_FMT_TXT_LARGE 0\n#endif")
            with open(lv_conf_path, "w", encoding="utf-8") as f:
                f.write(content)
            print("Successfully patched lv_conf.h")
        elif "#define LV_FONT_FMT_TXT_LARGE 1" in content and "#ifndef LV_FONT_FMT_TXT_LARGE" not in content:
            content = content.replace("#define LV_FONT_FMT_TXT_LARGE 1", 
                                      "#ifndef LV_FONT_FMT_TXT_LARGE\n#define LV_FONT_FMT_TXT_LARGE 1\n#endif")
            with open(lv_conf_path, "w", encoding="utf-8") as f:
                f.write(content)
            print("Successfully patched lv_conf.h (was 1)")
        else:
            print("lv_conf.h is already patched or not found correctly.")
    else:
        print("lv_conf.h not found at", lv_conf_path)

env.Execute(patch_lv_conf)
