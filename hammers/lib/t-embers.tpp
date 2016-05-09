READ_BYTE 0x1e usab1
READ_BYTE 0x1f usab2
READ_BYTE 0x20 usab3
READ_BYTE 0x21 usab4
READ_BYTE 0x29 ukit1
READ_BYTE 0x2b ukit2
READ_BYTE 0x2d ukit3
READ_BYTE 0x2f ukit4
WRITE_BYTE 0x1e (usab1 BAND 0b00111111) //Alignments
WRITE_BYTE 0x1f (usab2 BAND 0b00000000)
WRITE_BYTE 0x20 (usab3 BAND 0b10000000) //Elf
WRITE_BYTE 0x21 (usab4 BAND 0b10011111) //Races
WRITE_BYTE 0x29 (ukit1 BAND 0b00000000)
READ_BYTE 0x31 wp //Proficiency
PATCH_IF wp < 0x66 BEGIN
  WRITE_BYTE 0x2b (ukit2 BAND 0b00000010) //Beastmaster
END ELSE BEGIN
  WRITE_BYTE 0x2b (ukit2 BAND 0b00000000)
END
WRITE_BYTE 0x2d (ukit3 BAND 0b00000000)
WRITE_BYTE 0x2f (ukit4 BAND 0b00000000)