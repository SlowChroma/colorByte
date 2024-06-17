int * byte_to_rgba(char input[])
{
  static int result[4] = {0, 0, 0, 0};
  
  if(input[0] == '1') result[0] += 170;
  if(input[1] == '1') result[0] += 85;
  if(input[2] == '1') result[1] += 170;
  if(input[3] == '1') result[1] += 85;
  if(input[4] == '1') result[2] += 170;
  if(input[5] == '1') result[2] += 85;
  if(input[6] == '1') result[3] += 170;
  if(input[7] == '1') result[3] += 85;
  
  return result;
}
