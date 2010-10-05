file = [placI185_dna.xml]

MoDeL
{
	species id = [placI185_dna], name = [placI185 dna]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[dna that contains placI185];
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
							partReference:[ANY];
							partLabel:[X0];
							partType:[ForwardDNA];
							partCategory:[substituent];
						}
						part
						{
							partReference:[placI185];
							partLabel:[placI185];
							partType:[ForwardDNA];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
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
			referencedReaction:[bid_placI185_lacI153_4] speciesType = [reactant];
		}
	}
}
