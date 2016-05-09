PATCH_IF !(~%SOURCE_FILE%~ STRING_MATCHES_REGEXP ~^.+\.spl~) BEGIN
  hs = 0x28 //Extended header size
END ELSE PATCH_IF !(~%SOURCE_FILE%~ STRING_MATCHES_REGEXP ~^.+\.itm~) BEGIN
  hs = 0x38
END
READ_LONG 0x64 hf //Extended header offset
READ_SHORT 0x68 hc //Extended header count
READ_LONG 0x6a fb //Feature block offset
FOR (i1 = 1; i1 < hc; i1 += 1) BEGIN //Cycle through extended headers
  PATCH_IF (hc > 1) BEGIN //Remove dead headers on items
    READ_SHORT (hs * i1 + hf + 0x1e) fc //Feature count
    READ_SHORT (hs * i1 + hf + 0x20) fs //Feature offset
    DELETE_BYTES (fs * 0x30 + fb) (fc * 0x30) //Delete all effects
    WRITE_SHORT (hs * i1 + hf + 0x1e) 0 //Update feature count
    FOR (i4 = i1; i4 < hc; i4 += 1) BEGIN //Update 1st effect indices
      READ_SHORT (hs * i4 + hf + 0x20) fs //1st effect index
      WRITE_SHORT (hf + i4 * hs + 0x20) (fs - fc) //Decrease 1st effect index by fc
    END
    DELETE_BYTES (hs * i1 + hf) hs //Delete header
    hc -= 1
    WRITE_SHORT 0x68 hc //Update header count
    WRITE_LONG 0x6a (fb - hs) //Update feature block offset
  END
END
