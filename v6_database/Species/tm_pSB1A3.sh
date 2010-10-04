file = [tm_pSB1A3.xml]

MoDeL
{
	species id = [tm_pSB1A3], name = [plasmid with pSB1A3]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[plasmid containing backbone pSB1A3];
		}
		cnModel
		{
			listOfChains
			{
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[X];
							partLabel:[X0];
							partType:[ForwardDNA];
							partCategory:[substituent];
						}
						part
						{
							partReference:[pSB1A3];
							partLabel:[pSB1A3];
							partType:[ForwardDNA];
							partCategory:[ForwardDNA];
						}
						part
						{
							partReference:[X];
							partLabel:[X1];
							partType:[ForwardDNA];
							partCategory:[substituent];
						}
					}
				}
			}
			listOfTrees
			{
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[deg_ampicillin_by_pSB1A3] speciesType = [modifier];
		}
	}
}
