#include "read_infor.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

error_code_t read_boot_sector(BootSector_t *bs)
{
    HAL_fseek(0);
    if (HAL_fread(bs, sizeof(BootSector_t), 1) != 1)
    {
        return ERROR_READ_FAILURE;
    }
    if (bs->bytesPerSector != 512)
    {
        return ERROR_INVALID_PARAMETER;
    }
    return ERROR_OK;
}

uint16_t getRootDirStart(const BootSector_t *bs)
{
    uint32_t rootDirSector = bs->reservedSectors + (bs->numberOfFATs * bs->sectorsPerFAT16);
    return rootDirSector * bs->bytesPerSector;
}

error_code_t getEntryInRoot(const BootSector_t *bs, DirectoryEntry_t *entryOut)
{
    if (HAL_fread(entryOut, sizeof(DirectoryEntry_t), 1) != 1)
    {
        return ERROR_READ_FAILURE;
    }
    return ERROR_OK;
}

error_code_t findNameInRoot(
    const BootSector_t *bs,
    char *filename,
    DirectoryEntry_t *entryOput,
    uint8_t attribute)
{
    HAL_fseek(getRootDirStart(bs));
    int i;
    for (i = 0; i < bs->rootEntryCount; i++)
    {
        if (getEntryInRoot(bs, entryOput) != ERROR_OK)
        {
            return ERROR_INVALID_NAME;
        }
        else
        {
            if (entryOput->name[0] == 0x00)
            {
                continue;
            }
            if (entryOput->name[0] != (char)0xE5)
            {
                if (compareFileName(entryOput, filename))
                {
                    if (entryOput->attr == ATTR_DIRECTORY)
                    {
                        return attribute ? ERROR_OK : ERROR_WRONG_ATTRIBUTE;
                    }
                    else
                    {
                        return attribute ? ERROR_WRONG_ATTRIBUTE : ERROR_OK;
                    }
                }
            }
        }
    }
    return ERROR_INVALID_NAME;
}



int8_t compareFileName(DirectoryEntry_t *entryOput, const char *filename)
{
    char entryNameCopy[13] = {0};
    strncpy(entryNameCopy, entryOput->name, 8);
    entryNameCopy[8] = '\0';

    int i;
    for (i = strlen(entryNameCopy) - 1; i >= 0 && entryNameCopy[i] == ' '; i--)
    {
        entryNameCopy[i] = '\0';
    }

    if ((entryOput->attr & ATTR_DIRECTORY) == 0 && entryOput->ext[0] != ' ')
    {
        strncat(entryNameCopy, ".", 1);
        strncat(entryNameCopy, entryOput->ext, 3);
    }

    for (i = strlen(entryNameCopy) - 1; i >= 0 && entryNameCopy[i] == ' '; i--)
    {
        entryNameCopy[i] = '\0';
    }

    return strcmp(entryNameCopy, filename) == 0;
}
