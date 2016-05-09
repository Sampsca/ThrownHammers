READ_LONG 0x64 hf //Extended header offset
READ_SHORT 0x68 hc //Extended header count
READ_LONG 0x6a fb //Feature block offset
FOR (i1 = 1; i1 < hc; i1 = i1 + 1) BEGIN //Cycle through extended headers
  READ_SHORT (hf + 0x1e + (0x28 * i1)) fc //Feature count
  READ_SHORT (hf + 0x20 + (0x28 * i1)) fs //Feature offset
  FOR (i2 = fs; i2 < (fs + fc); i2 = i2 + 1) BEGIN //Cycle through ability effects
    READ_SHORT (fb + 0x30 * i2) pc //Opcode
    PATCH_IF ((pc = pd) OR (pd = (0 - 1))) BEGIN //Match or delete all
      DELETE_BYTES (fb + 0x30 * i2) 0x30
      fc = fc - 1 //Stop cycle properly
      WRITE_SHORT (hf + 0x1e + (0x28 * i1)) fc //Correct number of effects in ability
      FOR (i3 = 0; i3 < hc; i3 = i3 + 1) BEGIN //Correct 1st effect indices
        READ_SHORT (hf + i3 * 0x28 + 0x20) fx //1st effect index
        PATCH_IF (fx > i2) BEGIN //If next ability
          WRITE_SHORT (hf + i3 * 0x28 + 0x20) (fx - 1) //Decrease 1st effect i1 by 1
        END
      END
      i2 = i2 - 1 //Step back to not miss an effect
    END
  END
END
pd = 0 //Opcode to delete
